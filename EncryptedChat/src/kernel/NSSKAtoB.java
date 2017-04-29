package kernel;

import java.io.Serializable;

//NSSK协议中，A发给B的数据，包含了A的必要信息；该数据是由服务器加密后发给A，A转发给B的
public class NSSKAtoB implements Serializable {
	private static final long serialVersionUID = 8115899508091419970L;
	public byte[] sessionKey;  //A与B通信的会话秘钥
	public int AID;    //A的全局唯一标识
	public String AIP; //A的IP地址
	public int APort;  //A监听的端口号
	public NSSKAtoB(byte[] s, int a, String ai, int ap)
	{
		sessionKey = s;
		AID = a;
		AIP = ai;
		APort = ap;
	}
}
