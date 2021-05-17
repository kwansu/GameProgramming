using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public static class LinkedListExtention
{
    public static bool Remove<T>(this LinkedList<T> linkedList, Predicate<T> predicate)
    {
        for (LinkedListNode<T> node = linkedList.First; node != null; node = node.Next)
        {
            if (predicate(node.Value))
            {
                linkedList.Remove(node);
                return true;
            }
        }

        return false;
    }

    public static LinkedListNode<T> Find<T>(this LinkedList<T> linkedList, Predicate<T> predicate)
    {
        for (LinkedListNode<T> node = linkedList.First; node != null; node = node.Next)
        {
            if (predicate(node.Value))
            {
                return node;
            }
        }

        return null;
    }
}
