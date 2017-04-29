package kernel;

import java.io.UnsupportedEncodingException;
import java.util.BitSet;

public class DES extends CipherBase{

    /*
     * 用key加密data；key是128bit(16B)
     * 如果key与当前对象已有的秘钥不一致，就替换当前的秘钥
     * */
    @Override
    public byte[] encrypt(byte[] data, byte[] key) {
        
        if(!inited || !isBytesEqual(key, keyBack))
        {
            initKey(key);
        }
        return encrypt(data);
    }

    /*
     * 用key解密data；key是128bit(16B)
     * 如果key与当前对象已有的秘钥不一致，就替换当前的秘钥
     * */
    @Override
    public byte[] decrypt(byte[] data, byte[] key) {
        if(!inited || !isBytesEqual(key, keyBack))
        {
            initKey(key);
            inited = true;
        }
        return decrypt(data);
    }

    /*
     * 用对象已有的秘钥加密数据；如果当前对象还未被初始化，则返回null
     * */
    @Override
    public byte[] encrypt(byte[] data) {
        if(!inited)
            return null;
        byte[] text = padding(data);
        
        //block之间没有关联
        for(int i = 0;i < data.length;i+=8)
            enBlock(text, i);
        return text;
    }

    /*
     * 用对象已有的秘钥解密数据；如果当前对象还未被初始化，则返回null
     * */
    @Override
    public byte[] decrypt(byte[] data) {
        if(!inited)
            return null;
        
        //block之间没有关联
        for(int i = 0;i < data.length;i+=8)
            deBlock(data,i);
        return removePadding(data);
    }
    
    public DES()
    {
        Kn = new BitSet[16];
        inited = false;
    }
    
    //DES的64bit秘钥
    public DES(byte[] k)
    {
        Kn = new BitSet[16];
        initKey(k);
        inited = true;
    }
    
    /*
     * 字符串作为秘钥；计算字符串的MD5值，把MD5的前64bit与后64bit
     * 做异或运算后，作为DES的秘钥
     * */
    public DES(String key)
    {
        Kn = new BitSet[16];
        try {
            byte[] temp = key.getBytes("UTF-8");
            temp = calcMD5(temp);
            byte[] ky = new byte[8];
            for(int i = 0;i < 8;i++)
                ky[i] = (byte) (temp[i] | temp[i+8]);
            initKey(ky);
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }

    /*
     * 从plain的start位置开始，加密一个block；
     * 加密后的结果仍存到plain的相应位置
     * */
    protected void enBlock(byte[] plain, int start)
    {
        //IP置换
        BitSet LR = perm(bytesToBitSet(plain, start, start+8), IP);
        BitSet L0 = LR.get(0, 32);
        BitSet R0 = LR.get(32, 64);
        BitSet L1 = null, R1 = null;
        for(int i = 0;i < 16;i++)
        {
            L1 = R0;
            L0.xor(f(R0, Kn[i]));
            R1 = L0;
            L0 = L1;
            R0 = R1;
        }
        int j = 0;
        for(;j < 32;j++)
            LR.set(j, R1.get(j));
        for(;j < 64;j++)
            LR.set(j, L1.get(j-32));
        
        //IP逆置换
        bitSetToBytes(plain, start, start+8,perm(LR, IPINV));
    }
    
    /*
     * 从cipher的start位置开始，解密一个block；
     * 解密后的结果仍存到cipher的相应位置
     * */
    protected void deBlock(byte[] cipher, int start)
    {
        //IP置换
        BitSet RL = perm(bytesToBitSet(cipher, start, start+8), IP);
        BitSet Rn = RL.get(0, 32);
        BitSet Ln = RL.get(32, 64);
        BitSet Rn1 = null, Ln1 = null;
        for(int i = 15;i >= 0;i--)
        {
            Rn1 = Ln;
            Rn.xor(f(Ln, Kn[i]));
            Ln1 = Rn;
            Ln = Ln1;
            Rn = Rn1;
        }
        int j = 0;
        for(;j < 32;j++)
            RL.set(j, Ln1.get(j));
        for(;j < 64;j++)
            RL.set(j, Rn1.get(j - 32));
        //IP逆置换
        bitSetToBytes(cipher, start, start+8,perm(RL, IPINV));
    }
    
    /*
     * 计算DES的16个key；计算的结果存储在Kn数组中；
     * 在之后的加密或解密中会用到
     * */
    protected void initKey(byte[] k)
    {
        assert k.length == 8;//检查是否是64bit(8B)
        keyBack = k;
        BitSet key = bytesToBitSet(k, 0, k.length);
        
        //PC1置换
        BitSet C0 = perm(key, PC1C);
        BitSet D0 = perm(key, PC1D);
        BitSet CD = new BitSet(56);
        for(int i = 0;i < 16;i++)
        {
            rolBitSet(C0, ROL[i]);
            rolBitSet(D0, ROL[i]);
            int j = 0;
            for(;j < 28;j++)
                CD.set(j, C0.get(j));
            for(;j < 56;j++)
                CD.set(j, D0.get(j - 28));
            
            //执行PC2置换；得到相应的key
            Kn[i] = perm(CD, PC2);
        }
        inited = true;
    }

    /*
     * 将从data的start(包含)到end(不包含)的字节转化为BitSet对象
     * 比如01011101 11000110B将转成
     * {1, 3, 4, 5, 7, 8, 9, 13, 14}
     * */
    private BitSet bytesToBitSet(byte[] data, int start, int end)
    {
        BitSet bs = new BitSet((end - start)*8);
        for(int i = 0;i < (end - start);i++)
        {
            for(int j = 0;j < 8;j++)
                bs.set(8*i+j, (data[start+i]&ror[j]) != 0x00);
        }
        return bs;
    }

    /*
     * 将data转换为字节数组存至buf(从start位置开始)
     * 此过程是bytesToBitSet的逆过程
     * */
    private void bitSetToBytes(byte[] buf, int start, int end, BitSet data)
    {
        for(int i = 0;i < (end-start);i++)
        {
            byte temp = 0x00;
            for(int j = 0;j < 8;j++)
            {
                if(data.get(8*i+j))
                    temp |= ror[j];
                else
                    temp &= ~ror[j];
            }
            buf[start+i] = temp;
        }
    }
    
    /*
     * 将dat循环左移c位；操作直接在dat上进行
     * */
    private void rolBitSet(BitSet dat, int c)
    {
        BitSet left = dat.get(0, c);
        for(int i = c;i < 28;i++)
            dat.set(i - c, dat.get(i));
        for(int i = 0;i < c;i++)
            dat.set(28 - c + i, left.get(i));
    }

    /*
     * 对dat执行p置换；返回置换后的结果
     * 即permed[i]=dat[p[i]-1]
     * 注意：p中的索引是从1开始的；而dat和permed中的索引是从0开始的
     * */
    private BitSet perm(BitSet dat, int[] p)
    {
        BitSet permed = new BitSet(p.length);
        for(int i = 0;i < p.length;i++)
            permed.set(i, dat.get(p[i] - 1));
        return permed;
    }
    
    /*
     * DES中的f函数
     * */
    private BitSet f(BitSet r, BitSet k)
    {
        //E置换
        BitSet er = perm(r, E);
        
        //注意不能在r上直接操作，即此函数不能修改r的值
        BitSet rClone = (BitSet) r.clone();
        
        //模2加法
        er.xor(k);
        int p = 0, ri = 0;
        for(int i = 0;i < 8;i++, p+=6, ri+=4)
        {
            int row = (er.get(p)?2:0) + (er.get(p+5)?1:0);
            int col = (er.get(p+1)?8:0)
                    + (er.get(p+2)?4:0)
                    + (er.get(p+3)?2:0)
                    + (er.get(p+4)?1:0);
            
            //S查找函数
            BitSet temp = cvt[S[i][row][col]];
            for(int j = 0;j < 4;j++)
                rClone.set(ri+j, temp.get(j));
        }
        
        //P置换
        return perm(rClone, P);
    }
    
    //存储16个key
    private BitSet[] Kn;
    
    //key是否已初始化
    private boolean inited;
    
    //备份目前的key
    private byte[] keyBack;
    
    static final byte[] ror = {(byte) 0x80, 0x40, 0x20, 0x10,
            0x08, 0x04, 0x02, 0x01};
    
    //把0-15的数字转换为一个BitSet对象
    static BitSet[] cvt;
    static{
        cvt = new BitSet[16];
        for(int i = 0;i < 16;i++)
        {
            cvt[i] = new BitSet(4);
            int n = i;
            for(int j = 3;j >= 0 && n > 0;j++)
            {
                cvt[i].set(j, n%2 == 1);
                n /= 2;
            }
        }
    }
    //以下是DES标准中规定的常量；参考FIPS PUB 46-3
    static final int IP[] = 
        {   
                58,50,42,34,26,18,10,2,
                60,52,44,36,28,20,12,4,
                62,54,46,38,30,22,14,6,
                64,56,48,40,32,24,16,8,
                57,49,41,33,25,17,9,1,
                59,51,43,35,27,19,11,3,
                61,53,45,37,29,21,13,5,
                63,55,47,39,31,23,15,7
        };
    
    static final int IPINV[] = 
        {
                40,8,48,16,56,24,64,32,
                39,7,47,15,55,23,63,31,
                38,6,46,14,54,22,62,30,
                37,5,45,13,53,21,61,29,
                36,4,44,12,52,20,60,28,
                35,3,43,11,51,19,59,27,
                34,2,42,10,50,18,58,26,
                33,1,41,9,49,17,57,25
        };
    
    static final int E[] = 
        {
                32,1,2,3,4,5,
                4,5,6,7,8,9,
                8,9,10,11,12,13,
                12,13,14,15,16,17,
                16,17,18,19,20,21,
                20,21,22,23,24,25,
                24,25,26,27,28,29,
                28,29,30,31,32,1
        };
    
    static final int P[] = 
        {
                16,7,20,21,
                29,12,28,17,
                1,15,23,26,
                5,18,31,10,
                2,8,24,14,
                32,27,3,9,
                19,13,30,6,
                22,11,4,25
        };
    
    /*
     * S1第4行第8列：S[0][3][7]
     * S7第1行第15列：S[6][0][14]
     * */
    static final int S[][][] = 
        {
            {
                {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
                {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
                {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
            },//S1
            {
                {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
                {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
                {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
            },//S2
            {
                {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
                {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
                {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
            },//S3
            {
                {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
                {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
                {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
            },//S4
            {
                {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
                {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
                {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
            },//S5
            {
                {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
                {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
                {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
            },//S6
            {
                {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
                {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
                {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
            },//S7
            {
                {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
                {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
                {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
                {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
            }//S8
        };
    
    static final int ROL[] = 
        {
                1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
        };
    
    static final int PC1C[] = 
        {
                57,49,41,33,25,17,9,
                1,58,50,42,34,26,18,
                10,2,59,51,43,35,27,
                19,11,3,60,52,44,36
        };
    
    static final int PC1D[] = 
        {
                63,55,47,39,31,23,15,
                7,62,54,46,38,30,22,
                14,6,61,53,45,37,29,
                21,13,5,28,20,12,4
        };
    
    static final int PC2[] = 
        {
                14,17,11,24,1,5,
                3,28,15,6,21,10,
                23,19,12,4,26,8,
                16,7,27,20,13,2,
                41,52,31,37,47,55,
                30,40,51,45,33,48,
                44,49,39,56,34,53,
                46,42,50,36,29,32
        };
}
