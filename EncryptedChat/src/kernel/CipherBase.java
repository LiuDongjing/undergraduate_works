package kernel;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Random;

public abstract class CipherBase {
	
	public abstract byte[] encrypt(byte[] data, byte[] key);
	
	public abstract byte[] decrypt(byte[] data, byte[] key);
	
	public abstract byte[] encrypt(byte[] data);
    
    public abstract byte[] decrypt(byte[] data);

    static final int BlockSize = 8;
    
	//生成随机秘钥；16字节长
	public byte[] genRandomKey()
	{
		Random ran = new Random();
		byte[] temp = new byte[16];
		for(int i=0;i < 16;i++)
			temp[i] = (byte) ran.nextInt(256);
		return calcMD5(temp);
	}
	
	//计算MD5
	public byte[] calcMD5(byte[] data)
	{
		byte[] ret = null;
		try {
			MessageDigest md5 = MessageDigest.getInstance("MD5");
			md5.update(data);
			ret = md5.digest();
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
		return ret;
	}
	
	//字节数组减1
	public byte[] decBytes(byte[] data)
	{
		byte[] ret = data.clone();
		for(int i= ret.length - 1;i >= 0;i--)
		{
			if(ret[i] == 0x00)
			{
				ret[i] = (byte) 0xff;
				continue;
			}
			ret[i]-=1;
			break;
		}
		return ret;
	}
	
	//判断两个字节数组是否相等
	public boolean isBytesEqual(byte[] a, byte[] b)
	{
		if(a == null || b == null)
		    return false;
	    if(a.length != b.length)
			return false;
		for(int i=0;i < a.length;i++)
			if(a[i] != b[i])
				return false;
		return true;
	}
	
	//实现了PKCS7中的padding方案
	public static byte[] padding(byte[] data)
	{
	    int sz = BlockSize- (data.length % BlockSize);
	    byte[] pad = new byte[data.length + sz];
	    int i = 0;
	    for(;i < data.length;i++)
	        pad[i] = data[i];
	    for(;i < pad.length;i++)
	        pad[i] = (byte) sz;
	    return pad;
	}
	
	//移除padding
	public static byte[] removePadding(byte[] data)
	{
	    int sz = data[data.length - 1];
	    byte[] rmd = new byte[data.length - sz];
	    for(int i = 0;i < rmd.length;i++)
	        rmd[i] = data[i];
	    return rmd;
	}
}
