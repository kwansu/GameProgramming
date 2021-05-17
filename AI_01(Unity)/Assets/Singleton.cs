using System;
using System.Collections;
using System.Collections.Generic;

/// <summary>
/// 이걸 상속한다고 해도 생성자가 private하지 못하기 때문에
/// 단일성에서 문제가 발생한다. 즉, 이건 편의를 위한거지 상속받은 클래스에서
/// 각자 sealed 키워드와 private 생성자를 따로 만들어서 유일성을 만들어야한다.
/// </summary>
/// <typeparam name="T"></typeparam>
public class Singleton<T> where T : Singleton<T>
{
    static private T singletonInstance;

    static public T SingletonInstance
    {
        get
        {
            if (singletonInstance == null)
            {
                singletonInstance = (T)new Singleton<T>();
            }

            return singletonInstance;
        }
    }
}

