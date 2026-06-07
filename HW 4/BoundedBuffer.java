/**
 * Quotes from instructions:
 * A thread-safe circular Buffer that satisfies the FIFO property and is restricted to hold 
 * at most 1000 items at a time.
 * Producer threads call store() to add items; consumer threads call retrieve() to remove them.
 * Synchronization uses only wait() and notify() as required by the assignment.
 *
 * @author Anna Marie Love
 */
public class BoundedBuffer {

    /** The array of doubles that backs this buffer */
    private double[] buffer;

    /** Max of 1000 */
    private static final int CAPACITY = 1000;

    /** Producer writes here */
    private int tail;

    /** Consumer reads from her. */
    private int head;

    /** Count of items in buff */
    private int count;

    /**
     * Initialize buffer array. Set head, tail, and count to zero
     */
    public BoundedBuffer() {
        buffer = new double[CAPACITY];
        head = 0;
        tail = 0;
        count = 0;
    }

    /**
     * Called by the Producer
     * If the buffer is full the producer waits
     *
     * @param item the double value to add to the buffer
     */
    public synchronized void store(double item) {

        // Wait while the buffer is full
        try {
            while (count == CAPACITY) {
                wait();
            }
        } catch (InterruptedException e) {}

        // Insert item advance tail circularly
        buffer[tail] = item;
        tail = (tail + 1) % CAPACITY;
        count++;

        // Wake up the consumer 
        notify();
    }

    /**
     * Called by the Consumer
     * If the buffer is empty the consumer waits
     *
     * @return the next double value from the front of the buffer
     */
    public synchronized double retrieve() {

        // Wait while the buffer is empty
        try {
            while (count == 0) {
                wait();
            }
        } catch (InterruptedException e) {}

        // Remove item advance head circularly
        double item = buffer[head];
        head = (head + 1) % CAPACITY;
        count--;

        // Wake up the producer
        notify();

        return item;
    }
}
