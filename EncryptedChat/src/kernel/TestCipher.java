package kernel;

import java.io.UnsupportedEncodingException;

public class TestCipher {
public static void main(String[] args) throws UnsupportedEncodingException
    {
        byte[] data = "BESTWISHFORYOU".getBytes("UTF-8");
//        byte[] key1 = "WILLGIRL".getBytes("UTF-8");
//        byte[] key2 = "WILLLOVE".getBytes("UTF-8");
//        byte[] key3 = "LOVEGIRL".getBytes("UTF-8");
//        TDEA en = new TDEA(key1, key2, key3);
//        byte[] cipher = en.encrypt(data);
//        byte[] d = en.decrypt(cipher);
        TDEA des = new TDEA("hahahahah");
        byte[] x = des.encrypt(data);
        x = des.decrypt(x);
        String plain = new String(x, "UTF-8");
        System.out.println(plain);
        byte[] y = des.encrypt(data, "1234567890123456".getBytes("UTF-8"));
        byte[] z = des.decrypt(y, "1234567890123456".getBytes("UTF-8"));
        
        System.out.println(new String(z, "UTF-8"));
    }
}
