package kernel;

import java.io.UnsupportedEncodingException;

public class TDEA extends CipherBase {

    @Override
    public byte[] encrypt(byte[] data, byte[] key) {
        if(!isBytesEqual(keyBack, key))
        {
            initKey(key);
        }
        return encrypt(data);
    }

    @Override
    public byte[] decrypt(byte[] data, byte[] key) {
        if(!isBytesEqual(keyBack, key))
        {
            initKey(key);
        }
        return decrypt(data);
    }
    
    /*
     * 加密过程
     *  I -> DES Ek1 -> DES Dk2 -> DES Ek3 -> O
     *  */
    @Override
    public byte[] encrypt(byte[] data) {
        if(!inited)
            return null;
        byte[] text = padding(data);
        for(int i = 0;i < text.length;i+=8)
        {
            des1.enBlock(text, i);
            des2.deBlock(text, i);
            des3.enBlock(text, i);
        }
        return text;
    }

    /*
     * 解密过程
     *  I -> DES Dk3 -> DES Ek2 -> DES Dk1 -> O
     * */
    @Override
    public byte[] decrypt(byte[] data) {
        if(!inited)
            return null;
        for(int i = 0;i < data.length;i+=8)
        {
            des3.deBlock(data, i);
            des2.enBlock(data, i);
            des1.deBlock(data, i);
        }
        return removePadding(data);
    }
    
    private DES des1;
    private DES des2;
    private DES des3;
    private boolean inited;
    private byte[] keyBack;
    public TDEA()
    {
        des1 = new DES();
        des2 = new DES();
        des3 = new DES();
        inited = false;
    }
    
    //三个不同的key
    public TDEA(byte[] k1, byte[] k2, byte[] k3)
    {
        keyBack = new byte[k1.length+k2.length+k3.length];
        int i = 0;
        for(;i < k1.length;i++)
            keyBack[i] = k1[i];
        for(;i < k1.length + k2.length;i++)
            keyBack[i] = k2[i-k1.length];
        for(;i < keyBack.length;i++)
            keyBack[i] = k3[i-k1.length-k2.length];
        des1 = new DES(k1);
        des2 = new DES(k2);
        des3 = new DES(k3);
        inited = true;
    }
    
    //用MD5值初始化秘钥；k1 == k3
    public TDEA(byte[] ks)
    {
        this();
        initKey(ks);
    }
    
    //计算字符串的MD5值；k1 == k3
    public TDEA(String k)
    {
        this();
        try {
            initKey(calcMD5(k.getBytes("UTF-8")));
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }
    private void initKey(byte[] ks)
    {
        byte[] k1 = new byte[8];
        byte[] k2 = new byte[8];
        for(int i = 0;i < 8;i++)
        {
            k1[i] = ks[i];
            k2[i] = ks[i+8];
        }
        byte[] k3 = k1.clone();
        des1.initKey(k1);
        des2.initKey(k2);
        des3.initKey(k3);
        keyBack = ks;
        inited = true;
    }
}
