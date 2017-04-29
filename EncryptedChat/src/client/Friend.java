package client;

public class Friend {

	public int UID;
	public String remark;//备注名
	public boolean isValid;//true表明可以直接与好友通信；false表示需要先向服务器请求会话秘钥
	public byte[] sessionKey;
	public String ip;//好友的ip
	public int port;//好友监听的端口号
	public Friend(int u, String r)
	{
		UID = u;
		remark = r;
		isValid = false;
		sessionKey = null;
		ip = null;
		port = -1;
	}
}
