package CS370 HW 4.Synchronized Blocks Tutorial;

public class SyncWorker implements Runnable {

    private int [] sharedResource;

    public SyncWorker(int [] sharedResource) {
        this.sharedResource = sharedResource;
    }

    public void run() {
        synchronized(this.sharedResource) {
            // Access the variables by index
            // Set indicies
        }
    }
    
}

// for hw 4 need bounded buffer class backed by an array of doubles. This is one way you can do it. 
/*
Create bounded buffer class in here and pass reference to your workers.

Or in buffer class defind store and recieve to sync on the double array which backs the class.

Shared mutable state is the bounded buffer object backed by array of doubles. 

This demonstrates how to use sync key word to DS and have thread safe access to the DS.
*/