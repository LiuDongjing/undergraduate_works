package kernel;

public class CipherSimple extends CipherBase{

	//简单的加密算法；将key添加到data的前面
	public byte[] encrypt(byte[] data, byte[] key)
	{
		byte[] ret = new byte[key.length + data.length];
		int i = 0;
		for(;i < key.length;i++)
			ret[i] = key[i];
		for(;i < ret.length;i++)
			ret[i] = data[i - key.length];
		return ret;
	}
	
	public byte[] decrypt(byte[] data, byte[] key)
	{
		byte[] ret = new byte[data.length - key.length];
		for(int i = key.length;i < data.length;i++)
			ret[i - key.length] = data[i];
		return ret;
	}

    @Override
    public byte[] encrypt(byte[] data) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public byte[] decrypt(byte[] data) {
        // TODO Auto-generated method stub
        return null;
    }
	
}
