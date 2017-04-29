package kernel;

import java.io.Serializable;

//NSSK协议中，S返回给A的信息，包含了B的信息和会话秘钥
public class NSSKStoA implements Serializable {
    private static final long serialVersionUID = -3955313929162248405L;
	public byte[] ANonce;  //A生成的随机数
	public byte[] sessionKey;//A与B的会话秘钥
	public int BID;    //B的全局唯一标识
	public String BIP; //B的IP地址
	public int BPort;  //B监听的端口号
	public byte[] wrap;//{K_AB, A}K_BS
	
	public NSSKStoA(byte[] a, byte[] s, int bid,String bip, int bp, byte[] w)
	{
		ANonce = a;
		sessionKey = s;
		BID = bid;
		BIP = bip;
		BPort = bp;
		wrap = w;
	}
}
