package kernel;

import java.io.Serializable;

//NSSK协议中，A发给服务器的数据，包含了A自身的信息和想要通信的好友的编号
public class NSSKAtoS implements Serializable {
    private static final long serialVersionUID = -515454427839924853L;
	public int AID;    //A的全局唯一标识
	public int BID;    //B的全局唯一标识
	public byte[] nonce;//A生成的随机数
	public String AIP; //A的IP地址
	public int APort;  //A监听的端口号
	public NSSKAtoS(int mid, int fid, byte[] n, String ip, int p)
	{
		AID = mid;
		BID = fid;
		nonce = n;
		AIP = ip;
		APort = p;
	}
}
