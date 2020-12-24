using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace lab3
{
    class Lab3
    {
        object mutex = new object();
        Random rand = new Random();
        public List<int> ConsumersTimeList = new List<int>();
        public List<int> ProducersTimeList = new List<int>();
        public List<Thread> consumers = new List<Thread>();
        public List<Thread> producers = new List<Thread>();
        public Buffer<string> q = new Buffer<string>();
        public int NumberProces = 0;//счетчик

        public void Producer()
        {
            int number = ProducersTimeList.Count;
            int time = ProducersTimeList[number - 1];
            Console.WriteLine("Producer_{0} time={1}", number, time);

            while (true)
            {
                Thread.Sleep(Convert.ToInt32(time * 1000 * (rand.NextDouble() + 0.5)));//имитация выполнения
                if (q.queue.Count < 10)
                {
                    lock (mutex)
                    {
                        NumberProces++;
                        q.Enqueue("data_" + NumberProces.ToString());
                        Console.WriteLine("[{0}/10] Produser_{1} add data_{2}", q.queue.Count, number, NumberProces);
                    }

                }
            }
        }

        public void Consumer()
        {
            int number = ConsumersTimeList.Count;
            int time = ConsumersTimeList[number - 1];
            Console.WriteLine("Consumer_{0} time={1}", number, time);
            while (true)
            {
                string s = q.Dequeue();
                if (s == null) continue;

                Console.WriteLine("[{0}/10] Consumer_{1} pop {2}", q.queue.Count, number, s);
                Thread.Sleep(Convert.ToInt32(time * 1000 * (rand.NextDouble() + 0.5)));
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
            prodcons.ProducersTimeList.Add(1);
            prodcons.producers.Add(new Thread(prodcons.Producer));
            prodcons.producers[prodcons.producers.Count - 1].Start();
            Thread.Sleep(50);
            prodcons.ProducersTimeList.Add(2);
            prodcons.producers.Add(new Thread(prodcons.Producer));
            prodcons.producers[prodcons.producers.Count - 1].Start();
            Thread.Sleep(50);
            prodcons.ProducersTimeList.Add(3);
            prodcons.producers.Add(new Thread(prodcons.Producer));
            prodcons.producers[prodcons.producers.Count - 1].Start();
            Thread.Sleep(50);
            Console.WriteLine("");

            prodcons.ConsumersTimeList.Add(4);
            prodcons.consumers.Add(new Thread(prodcons.Consumer));
            prodcons.consumers[prodcons.consumers.Count - 1].Start();
            Thread.Sleep(50);
            prodcons.ConsumersTimeList.Add(5);
            prodcons.consumers.Add(new Thread(prodcons.Consumer));
            prodcons.consumers[prodcons.consumers.Count - 1].Start();
            Thread.Sleep(50);
            prodcons.ConsumersTimeList.Add(6);
            prodcons.consumers.Add(new Thread(prodcons.Consumer));
            prodcons.consumers[prodcons.consumers.Count - 1].Start();
            Thread.Sleep(50);
            Console.WriteLine("");

        }
    }
}
