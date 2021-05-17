using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace AutoOthelo
{
	class Program
	{
		static void Main(string[] args)
		{
			Action someAction = () =>
			{
				BoardManager manager = new BoardManager();

				manager.Process();
				Console.WriteLine("complete");
			};

			ThreadStart threadStart = new ThreadStart(someAction);

			Thread[] threads = new Thread[5];

			for (int i = 0; i < 5; ++i)
			{
				threads[i] = new Thread(threadStart);
				threads[i].Start();
			}

			foreach (var val in threads)
			{
				val.Join();
			}

			Console.WriteLine((float)BoardManager.win / BoardManager.total);

			Console.WriteLine("complete!!");
		}
	}
}
