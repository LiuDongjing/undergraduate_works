package kernel;

import java.io.Serializable;

//实现了C++中的Pair模板
public class Pair<T0, T1> implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 2114825552387382904L;

	private T0 first;
	private T1 second;
	public Pair(T0 f, T1 s)
	{
		first = f;
		second = s;
	}
	
	public T0 first()
	{
		return first;
	}
	public T1 second()
	{
		return second;
	}
}
