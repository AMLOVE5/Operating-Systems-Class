/**
 * Consumes 1,000,000 Double values from the BoundedBuffer
 * If the buffer is empty, the consumer will wait until an item is available
 * Prints a running total every 100,000 items and a final message when done
 *
 * @author Anna Marie Love
 */
public class Consumer implements Runnable {

    /** The shared buffer that this consumer reads from */
    private BoundedBuffer buffer;

    /**
     * Constructs a Consumer w/ reference to the shared BoundedBuffer
     *
     * @param buffer the shared bounded buffer
     */
    public Consumer(BoundedBuffer buffer) {
        this.buffer = buffer;
    }

    /**
     * Retrieves 1,000,000 Double values from the buffer
     * Prints according to ex
     */
    public void run() {

        double bufferValueCounter = 0.0;

        for (int i = 1; i <= 1000000; i++) {

            // Retrieve the next item from the front of the buffer
            double item = buffer.retrieve();
            bufferValueCounter += item;

            // Print progress every 100,000 items
            if (i % 100000 == 0) {
                System.out.println("Consumer: Consumed " + String.format("%,d", i) +
                        " items, Cumulative value of consumed items=" + String.format("%.3f", bufferValueCounter));
            }
        }

        System.out.println("Consumer: Finished consuming 1,000,000 items");
    }
}