using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace lab3
{
    class Lab3
    {
        object mutex = new object();
        public Random rand = new Random();
        public Buffer<string> buffer = new Buffer<string>();
        public int NumberProces = 0; //счетчик
        public int numProds = 0;
        public int numCons = 0;

        public void Producer()
        {
            int number = ++numProds;
            Console.WriteLine("Producer_{0}", number);

            while (true)
            {
                Thread.Sleep(Convert.ToInt32(rand.NextDouble() * 2000)); //имитация выполнения
                lock (mutex)
                {
                    if (buffer.queue.Count < 10)
                    {
                        NumberProces++;
                        buffer.Enqueue("data_" + NumberProces.ToString());
                        Console.WriteLine(string.Concat(Enumerable.Repeat("1", buffer.queue.Count)) + string.Concat(Enumerable.Repeat("_", 10 - buffer.queue.Count)));
                    }
                }
            }
        }

        public void Consumer()
        {
            int number = ++numCons;
            Console.WriteLine("Consumer_{0}", number);

            while (true)
            {
                Thread.Sleep(Convert.ToInt32(rand.NextDouble() * 3000));
                string s = buffer.Dequeue();
                if (s == null) continue;
                Console.WriteLine(string.Concat(Enumerable.Repeat("1", buffer.queue.Count)) + string.Concat(Enumerable.Repeat("_", 10 - buffer.queue.Count)));
            }
        }

    }

    public class Buffer<T> where T : class
    {
        object mutexEnqueue = new object();
        object mutexDequeue = new object();
        public Queue<T> queue = new Queue<T>();
        public T[] Q = new T[10];

        public void Enqueue(T task) 
        {
            if (task == null) throw new ArgumentNullException("task is null");
            lock (mutexEnqueue) queue.Enqueue(task);
        }

        public T Dequeue()//extract
        {
            lock (mutexDequeue)
            {
                if (queue.Count == 0) return null;
                return queue.Dequeue();
            }
        }
    }

    class Program
    {
        public static Lab3 prodcons = new Lab3();

        static void Main(string[] args)
        {
            (new Thread(prodcons.Producer)).Start();
            (new Thread(prodcons.Producer)).Start();
            (new Thread(prodcons.Producer)).Start();

            (new Thread(prodcons.Consumer)).Start();
            (new Thread(prodcons.Consumer)).Start();
            (new Thread(prodcons.Consumer)).Start();

        }
    }
}
