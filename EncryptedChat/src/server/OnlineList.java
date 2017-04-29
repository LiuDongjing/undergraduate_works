package server;

import java.util.HashMap;

//该类采用单例模式；相关内容参考 http://blog.csdn.net/jason0539/article/details/23297037
//在线用户的信息
public class OnlineList {

	private HashMap<Integer,AliveUser> data;
	
	private OnlineList()
	{
		data = new HashMap<Integer,AliveUser>();
	}
	
	private static final OnlineList Map = new OnlineList();
	
	public static OnlineList getInstance()
	{
		return Map;
	}
	
	boolean isUserOnline(int UID)
	{
		return data.containsKey(new Integer(UID));
	}
	
	void removeUser(Integer UID)
	{
		data.remove(UID);
	}
	
	void addUser(AliveUser user)
	{
		if(!isUserOnline(user.UID))
			data.put(user.UID, user);
	}
	
	AliveUser getUser(int UID)
	{
		return data.get(new Integer(UID));
	}
}
