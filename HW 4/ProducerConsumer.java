/**
 * Entry point
 * Creates one shared BoundedBuffer, one Producer, and one Consumer
 * Both the producer and consumer run concurrently on separate threads
 *
 * @author Anna Marie Love
 */
public class ProducerConsumer {

    /**
     * Creates the shared buffer, starts the producer and consumer threads,
     * and waits for both
     *
     * @param args (not used)
     */
    public static void main(String[] args) {

        // Create the single shared buffer
        BoundedBuffer buffer = new BoundedBuffer();

        // Create the producer and consumer
        Producer producer = new Producer(buffer);
        Consumer consumer = new Consumer(buffer);

        // Wrap
        Thread producerThread = new Thread(producer);
        Thread consumerThread = new Thread(consumer);

        producerThread.start();
        consumerThread.start();

        // Wait for both threads
        try {
            producerThread.join();
            consumerThread.join();
        } catch (InterruptedException e) {}

        System.out.println("Exiting!");
    }
}