package server;

import kernel.User;

//当前在线用户的信息
public class AliveUser {

	public int UID;
	public String ip;
	public int port;
	public byte[] pass;
	public AliveUser(int t_UID, User u)
	{
		UID = t_UID;
		ip = u.getIp();
		port = u.getPort();
		pass = u.passwordMD5();
	}
}
