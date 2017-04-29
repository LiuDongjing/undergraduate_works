package client;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.logging.Logger;

import kernel.CommandEnum;
import kernel.Session;
import kernel.User;

public class Main {

	public static void main(String[] args) {
		Socket socket = null;
		ObjectOutputStream objOuts = null;
		ObjectInputStream objIns = null;
		Session data = new Session(CommandEnum.UserRegister);
		Logger log = Logger.getLogger("client.Main.main");
		try {

			socket = new Socket(Configure.server_ip, Configure.server_port);
			log.info("与服务器" + Configure.server_ip + ":" + Configure.server_port + "成功建立连接！");
			objOuts = new ObjectOutputStream(socket.getOutputStream());
			objIns = new ObjectInputStream(socket.getInputStream());
			objOuts.writeObject(data);
			objOuts.writeObject(new User("test", "pass"));
			Session feedback = (Session) objIns.readObject();
			switch (feedback.command) {
			case Success:
				log.info("新用户注册成功！");
				break;
			case Failed:
				log.info("用户注册失败！");
			default:
				break;
			}
		} catch (Exception e) {

			e.printStackTrace();

		} finally {

			try {
				objOuts.close();
				socket.close();
			} catch (Exception e2) {
			}
		}
	}
}
