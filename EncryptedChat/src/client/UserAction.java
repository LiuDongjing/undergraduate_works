package client;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.logging.Level;
import java.util.logging.Logger;

import kernel.CipherBase;
import kernel.CipherSimple;
import kernel.CommandEnum;
import kernel.NSSKAtoS;
import kernel.NSSKStoA;
import kernel.Pair;
import kernel.Session;
import kernel.TDEA;
import kernel.Unity;
import kernel.User;

public class UserAction {

	private static Logger log;
	private static UserStatus status;
	static{
		log = Logger.getLogger("client.UserAction");
		status = UserStatus.getInstance();
	}
	
	//向服务器发送一个Session数据，并返回服务器发回的Session数据
	static Session WriteServer(Session data)
	{
		Socket socket = null;
		ObjectOutputStream objOuts = null;
		ObjectInputStream objIns = null;
		Session feedback = null;
		try {
			socket = new Socket(Configure.server_ip, Configure.server_port);
			objOuts = new ObjectOutputStream(socket.getOutputStream());
			objIns = new ObjectInputStream(socket.getInputStream());
			objOuts.writeObject(data);
			feedback = (Session) objIns.readObject();
		} catch (Exception e) {
			log.log(Level.SEVERE, "无法连接服务器("+Configure.server_ip+":"+Configure.server_port+")！出错原因如下："+e.getMessage());
		} finally {

			try {
				objIns.close();
				objOuts.close();
				socket.close();
			} catch (Exception e2) {
				log.log(Level.WARNING, e2.getMessage());
			}
		}
		return feedback;
	}
	
	//注册新用户；成功返回true，否则，返回false
	public static boolean Register(String name, String pass) {
		Socket socket = null;
		ObjectOutputStream objOuts = null;
		ObjectInputStream objIns = null;
		boolean opState = true;
		Session data = new Session(CommandEnum.UserRegister);
		try {
			socket = new Socket(Configure.server_ip, Configure.server_port);
			objOuts = new ObjectOutputStream(socket.getOutputStream());
			objIns = new ObjectInputStream(socket.getInputStream());
			objOuts.writeObject(data);
			objOuts.writeObject(new User(name, pass));
			Session feedback = (Session) objIns.readObject();
			if (CommandEnum.Success != feedback.command)
				opState = false;
		} catch (Exception e) {
			opState = false;
			log.log(Level.SEVERE, "无法连接服务器("+Configure.server_ip+":"+Configure.server_port+")！出错原因如下："+e.getMessage());
		} finally {

			try {
				objIns.close();
				objOuts.close();
				socket.close();
			} catch (Exception e2) {
				log.log(Level.SEVERE, e2.getMessage());
				opState = false;
			}
		}
		return opState;
	}
	
	//用户登陆
	public static boolean Login(String name, String pass)
	{
		if(status.isOnline())
		{
			log.log(Level.WARNING,"请先退出当前用户！");
			return false;
		}
		status.startListeningThread();
		Socket socket = null;
		ObjectOutputStream objOuts = null;
		ObjectInputStream objIns = null;
		boolean opState = true;
		Session data = new Session(CommandEnum.UserLogin);
		try {
			socket = new Socket(Configure.server_ip, Configure.server_port);
			log.log(Level.INFO, "已连接服务器("+Configure.server_ip+":"+Configure.server_port+")。");
			objOuts = new ObjectOutputStream(socket.getOutputStream());
			objIns = new ObjectInputStream(socket.getInputStream());
			objOuts.writeObject(data);
			User me = new User(name, pass, status.getIP(), status.getPort());
			objOuts.writeObject(me);
			Session feedback = (Session) objIns.readObject();
			if (CommandEnum.Success == feedback.command)
			{
				status.setName(name);
				@SuppressWarnings("unchecked")
				Pair<Integer, HashMap<Integer, String>> p = (Pair<Integer, HashMap<Integer, String>>)feedback.data;
				status.setUID((p.first()).intValue());
				status.setPass(me.passwordMD5());
				status.login();
				//存储好友的信息
				for(Entry<Integer, String> e:p.second().entrySet())
				{
					status.addFriend(e.getValue(), e.getKey());
				}
			}
			else
			{
				opState = false;
				log.log(Level.SEVERE, feedback.data.toString());
			}
		} catch (Exception e) {
			opState = false;
			log.log(Level.SEVERE, "无法连接服务器("+Configure.server_ip+":"+Configure.server_port+")！出错原因如下："+e.getMessage());
		} finally {

			try {
				objIns.close();
				objOuts.close();
				socket.close();
			} catch (Exception e2) {
				log.log(Level.WARNING, e2.getMessage());
				opState = false;
			}
		}
		if(!opState)
		    status.stopListeningThread();
		return opState;
	}
	
	//添加新朋友
	public static boolean AddFriend(int uid)
	{
		if(!status.isOnline())
		{
			log.log(Level.SEVERE, "请先登录！");
			return false;
		}
		Socket socket = null;
		ObjectOutputStream objOuts = null;
		ObjectInputStream objIns = null;
		boolean opState = true;
		Session data = new Session(CommandEnum.AddFriend, new Pair<Integer, Integer>(new Integer(status.getUID()), new Integer(uid)));
		try {
			socket = new Socket(Configure.server_ip, Configure.server_port);
			objOuts = new ObjectOutputStream(socket.getOutputStream());
			objIns = new ObjectInputStream(socket.getInputStream());
			objOuts.writeObject(data);
			Session feedback = (Session) objIns.readObject();
			if (CommandEnum.Success != feedback.command)
			{
				opState = false;
				log.log(Level.SEVERE, feedback.data.toString());
			}
		} catch (Exception e) {
			opState = false;
			log.log(Level.SEVERE, "无法连接服务器("+Configure.server_ip+":"+Configure.server_port+")！出错原因如下："+e.getMessage());
		} finally {

			try {
				objIns.close();
				objOuts.close();
				socket.close();
			} catch (Exception e2) {
				log.log(Level.WARNING, e2.getMessage());
				opState = false;
			}
		}
		return opState;
	}
	
	//NSSK通信的第三步及以后
	private static boolean notifyB(int bid, byte[] sessKey, String ip, int port, byte[] wrap)
	{
		boolean retS = true;
		Socket socket = null;
		ObjectInputStream objIns = null;
		ObjectOutputStream objOuts = null;
		Session sess = null;
		CipherBase cip = new TDEA();
		
		try {
			socket = new Socket(ip, port);
			objOuts = new ObjectOutputStream(socket.getOutputStream());
			objIns = new ObjectInputStream(socket.getInputStream());
			objOuts.writeObject(new Session(CommandEnum.NotifyB, wrap));
			try {
				byte[] Bnonce = cip.decrypt((byte[])objIns.readObject(),sessKey);
				Bnonce = cip.decBytes(Bnonce);
				objOuts.writeObject(cip.encrypt(Bnonce, sessKey));
				sess = (Session) objIns.readObject();
				if(sess.command == CommandEnum.Success)
				{
					//至此，双方成功建立连接
					status.updateFriend(bid, sessKey, ip, port);
				}
				else
					retS = false;
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
				retS = false;
			}
		} catch (UnknownHostException e) {
			e.printStackTrace();
			retS = false;
		} catch (IOException e) {
			e.printStackTrace();
			retS = false;
		}
		return retS;
	}
	
	//向friendUid发送消息
	public static boolean SendMessage(int friendUid, Object data)
	{
		boolean ret = true;
		byte[] sessKey = status.getFriendSesionKey(friendUid);
		if(sessKey == null)
		{
			ret = RequestCommunication(friendUid);
			if(ret)
			{
				sessKey = status.getFriendSesionKey(friendUid);
			}
		}
		if(sessKey != null)
		{
			CipherBase cib = new TDEA();
			Socket socket = null;
			try {
				socket = new Socket(status.getFriendIP(friendUid),
						status.getFriendPort(friendUid));
				ObjectOutputStream objOuts = new ObjectOutputStream(socket.getOutputStream());
				ObjectInputStream objIns = new ObjectInputStream(socket.getInputStream());
				objOuts.writeObject(new Session(CommandEnum.SendMessage, cib.encrypt(Unity.ObjectToBytes(data), sessKey), status.getUID()));
				Session retValue = (Session)objIns.readObject();
				if(retValue.command != CommandEnum.Success)
				{
					ret = false;
				}
			} catch (UnknownHostException e) {
				e.printStackTrace();
				ret = false;
			} catch (IOException e) {
				e.printStackTrace();
				ret = false;
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
				ret = false;
			}
		}
		//会话秘钥已过期
		if(!ret)
		{
			log.log(Level.WARNING, "与"+friendUid+"的会话秘钥已过期！");
			status.friends.get(new Integer(friendUid)).isValid = false;
		}
		return ret;
	}
	
	//NSSK协议的第一、二步；从服务器获取会话秘钥
	public static boolean RequestCommunication(int friendUid)
	{
		if(!status.isOnline())
		{
			log.log(Level.SEVERE, "请先登录！");
			return false;
		}
		Socket socket = null;
		ObjectOutputStream objOuts = null;
		ObjectInputStream objIns = null;
		
		boolean opState = true;
		Session data = new Session(CommandEnum.RequestCommunication, 
				new NSSKAtoS(status.getUID(), friendUid, (new TDEA()).genRandomKey(),
						status.getIP(), status.getPort()));
		try {
			socket = new Socket(Configure.server_ip, Configure.server_port);
			objOuts = new ObjectOutputStream(socket.getOutputStream());
			objIns = new ObjectInputStream(socket.getInputStream());
			objOuts.writeObject(data);
			Session feedback = (Session) objIns.readObject();
			if (CommandEnum.Success == feedback.command)
			{
				CipherBase cip = new TDEA();
				
				NSSKStoA nsa = (NSSKStoA)Unity.BytesToObject(cip.decrypt((byte[])feedback.data, status.getPass()));
				
				if(notifyB(friendUid, nsa.sessionKey,nsa.BIP,nsa.BPort,nsa.wrap))
				{
					log.log(Level.INFO, "成功与"+friendUid+"建立连接！");
				}
				else
				{
					log.log(Level.SEVERE, "与"+friendUid+"建立连接失败！");
					opState = false;
				}
			}
		} catch (Exception e) {
			opState = false;
			log.log(Level.SEVERE, "无法连接服务器("+Configure.server_ip+":"+Configure.server_port+")！出错原因如下："+e.getMessage());
		} finally {

			try {
				objIns.close();
				objOuts.close();
				socket.close();
			} catch (Exception e2) {
				log.log(Level.WARNING, e2.getMessage());
				opState = false;
			}
		}
		return opState;
	}
	
	//退出当前用户
	public static boolean Logoff()
	{
		boolean retVal = true;
		Session feed = WriteServer(new Session(CommandEnum.UserLogoff,
				new Integer(status.getUID())));
		status.clear();
		if(feed == null)
		{
			log.log(Level.SEVERE,"通信错误！详情请看日志！");
			retVal = false;
		}
		status.stopListeningThread();
		return retVal;
	}
	
	//删除好友
	public static boolean DeleteFriend(int uid)
	{
		Session feed = WriteServer(new Session(CommandEnum.DelFriend,
				new Pair<Integer,Integer>(new Integer(status.getUID()),
						new Integer(uid))));
		if(feed == null || feed.command != CommandEnum.Success)
		{
			log.log(Level.SEVERE, feed.data.toString());
			return false;
		}
		status.friends.remove(new Integer(uid));
		return true;
	}
	
	//修改好友的备注名
	public static boolean RenameFriend(int uid, String fresh)
	{
		Session feed = WriteServer(new Session(
				CommandEnum.RenameFriend,
				new Pair<Integer, Pair<Integer, String>>
					(new Integer(status.getUID()), 
							new Pair<Integer, String>
							(new Integer(uid), fresh))));
		if(feed == null || feed.command != CommandEnum.Success)
		{
			log.log(Level.SEVERE, feed.data.toString());
			return false;
		}
		status.friends.get(new Integer(uid)).remark = fresh;
		return true;
	}


	public static boolean Rename(String fresh)
	{
		Session feed = WriteServer(new Session(CommandEnum.Rename,
				new Pair<Integer,String>(new Integer(status.getUID()),
						fresh)));
		if(feed == null || feed.command != CommandEnum.Success)
		{
			log.log(Level.SEVERE, feed.data.toString());
			return false;
		}
		status.setName(fresh);
		return true;
	}
}
