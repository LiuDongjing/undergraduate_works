package client;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

import kernel.CipherBase;
import kernel.CipherSimple;
import kernel.CommandEnum;
import kernel.FileData;
import kernel.NSSKAtoB;
import kernel.Session;
import kernel.TDEA;
import kernel.Unity;

//处理来自另一个客户端的Socket连接
public class DispatchThread implements Runnable{

	private Thread thread;
	private Socket socket;
	private UserStatus status;
	private Logger log;
	public DispatchThread(Socket s)
	{
		thread = new Thread(this);
		socket = s;
		status = UserStatus.getInstance();
		log = Logger.getLogger("client.DispatchThread");
		thread.start();
	}
	
	public void run()
	{
		ObjectInputStream objIns = null;
		ObjectOutputStream objOuts = null;
		Session sess = null;
		CipherBase cib = new TDEA();
		try {
			objIns = new ObjectInputStream(socket.getInputStream());
			objOuts = new ObjectOutputStream(socket.getOutputStream());
			sess = (Session)objIns.readObject();
			switch(sess.command)
			{
			case NotifyB:
				NSSKAtoB nab = (NSSKAtoB)Unity.BytesToObject(cib.decrypt((byte[])sess.data, status.getPass()));
				byte[] nonce = cib.genRandomKey();
				objOuts.writeObject(cib.encrypt(nonce, nab.sessionKey));
				byte[] nonceDec = cib.decrypt((byte[])objIns.readObject(),nab.sessionKey);
				if(cib.isBytesEqual(nonceDec, cib.decBytes(nonce)))
				{
					objOuts.writeObject(new Session(CommandEnum.Success));
					status.updateFriend(nab);
				}
				else
					objOuts.writeObject(new Session(CommandEnum.Failed));
				break;
			case SendMessage:
				byte[] key = status.getFriendSesionKey(sess.from);
				Object message = Unity.BytesToObject(cib.decrypt((byte[])sess.data, key));
				if(message.getClass().equals(FileData.class))
				   log.log(Level.INFO, "来自"+sess.from+"的消息："+((FileData)message));
				else
				   log.log(Level.INFO, "来自"+sess.from+"的消息："+message);
				status.postMessage(sess.from, message);
				objOuts.writeObject(new Session(CommandEnum.Success));
			default:
				break;
			}
		} catch (IOException | ClassNotFoundException e) {
			e.printStackTrace();
		}
		try {
			objIns.close();
			objOuts.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
