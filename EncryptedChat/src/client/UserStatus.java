package client;

import java.util.HashMap;
import java.util.Map.Entry;

import gui.Window;
import kernel.NSSKAtoB;

//单例模式；记录了当前用户的状态信息
public class UserStatus {

	private UserStatus()
	{
		friends = new HashMap<Integer, Friend>();
		name = null;
		online  =false;
		listen = null;
		clientType = 0;
	}
	
	public int getClientType()
	{
	    return clientType;
	}
	public void setClientType(int c)
	{
	    clientType = c;
	}
	private static UserStatus status = new UserStatus();
	
	public static UserStatus getInstance()
	{
		return status;
	}
	
	private String name;
	private int UID;
	private String ip;
	private int port;
	private byte[] pass;
	private boolean online;
	private ListeningThread listen;
	private Window guiHandle;
	
	//客户端的类型；0表示命令行；1表示GUI界面
	private int clientType;
	
	public String toString()
	{
		String ret = "ID："+UID+"\n"+
					"名称："+name+"\n"+
					"绑定IP："+ip+"\n"+
					"监听端口："+port+"\n"+
					"好友信息"+"\n"+
					"ID\t备注\n";
		for(Entry<Integer,Friend> e:friends.entrySet())
		{
			ret+=e.getKey()+"\t"+e.getValue().remark+"\n";
		}		
		return ret;
	}
	
	public void clear()
	{
		name = null;
		UID = 0;
		pass = null;
		online  = false;
		friends.clear();
		stopListeningThread();
	}
	public void setWindow(Window w)
	{
	    guiHandle = w;
	}
	public void postMessage(int from, Object msg)
	{
	    if(clientType == 1)
	    {
	        guiHandle.newMessage(from, msg);
	    }
	}
	public void startListeningThread()
	{
		if(listen == null)
		 listen = new ListeningThread();
	}
	public void stopListeningThread()
	{
		if(listen != null)
		{
			listen.kill();
			listen = null;
		}
	}
	
	protected HashMap<Integer, Friend> friends;
	
	public boolean isOnline()
	{
		return online;
	}
	public void login()
	{
		online = true;
	}
	
	public void addFriend(String name, int uid)
	{
		friends.put(new Integer(uid), new Friend(uid, name));
	}
	
	public byte[] getFriendSesionKey(int uid)
	{
		Friend f = friends.get(new Integer(uid));
		if(f.isValid)
			return f.sessionKey;
		return null;
	}
	public String getFriendIP(int uid)
	{
		Friend f = friends.get(new Integer(uid));
		return f.ip;
	}
	public int getFriendPort(int uid)
	{
		Friend f = friends.get(new Integer(uid));
		return f.port;
	}
	public void updateFriend(int uid, byte[] sessKey, String ip, int port)
	{
		Friend f = friends.get(new Integer(uid));
		
		f.sessionKey = sessKey;
		f.ip = ip;
		f.isValid = true;
		f.port = port;
	}
	public void updateFriend(NSSKAtoB ab)
	{
		if(!isFriendExist(ab.AID))
		{
			addFriend(null, ab.AID);
		}
		updateFriend(ab.AID, ab.sessionKey, ab.AIP, ab.APort);
	}
	
	public boolean isFriendExist(int uid)
	{
		return friends.containsKey(new Integer(uid));
	}
	
	public String getName()
	{
		return name;
	}
	public void setName(String n)
	{
		name = n;
	}
	public int getUID()
	{
		return UID;
	}
	public void setUID(int u)
	{
		UID = u;
	}
	
	public String getIP()
	{
		return ip;
	}
	
	public void setIP(String i)
	{
		ip = i;
	}
	
	public int getPort()
	{
		return port;
	}
	
	public void setPort(int p)
	{
		port = p;
	}
	
	public byte[] getPass()
	{
		return pass;
	}
	
	public void setPass(byte[] p)
	{
		pass = p;
	}
	
	public HashMap<Integer, Friend> getFriends()
	{
	    return friends;
	}
}
