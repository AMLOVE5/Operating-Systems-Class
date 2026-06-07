import java.util.Random;

/**
 * Produces 1,000,000 random Double values and stores them in the BoundedBuffer
 * If the buffer is full, the producer will wait until space is available
 * Prints a running total every 100,000 items and a final message when done
 *
 * @author Anna Marie Love
 */
public class Producer implements Runnable {

    /** The shared buffer that this producer writes to */
    private BoundedBuffer buffer;

    /**
     * Constructs a Producer w/ reference to the shared BoundedBuffer.
     *
     * @param buffer the shared bounded buffer
     */
    public Producer(BoundedBuffer buffer) {
        this.buffer = buffer;
    }

    /**
     * Generates 1,000,000 random Double values and stores each one in the buffer
     * Prints according to ex
     */
    public void run() {

        Random random = new Random();
        double bufferValueCounter = 0.0;

        for (int i = 1; i <= 1000000; i++) {

            // Generate a random double between 0 and 100
            double item = random.nextDouble() * 100.0;

            buffer.store(item);
            bufferValueCounter += item;

            // Print progress every 100,000 items
            if (i % 100000 == 0) {
                System.out.println("Producer: Generated " + String.format("%,d", i) +
                        " items, Cumulative value of generated items=" + String.format("%.3f", bufferValueCounter));
            }
        }

        System.out.println("Producer: Finished generating 1,000,000 items");
    }
}