package hw5;

/**
 * Set implemented using a doubly linked list and move-to-front heuristic.
 *
 * @param <T> Element type.
 */
public class MoveToFrontLinkedSet<T> extends LinkedSet<T> {

  /**
   * Runs a MoveToFrontLinkedSet and its methods to ensure correct function.
   * @param args Is the main method
   */
  public static void main(String[] args) {
    MoveToFrontLinkedSet<Integer> set = new MoveToFrontLinkedSet<>();
    set.insert(3);
    set.insert(32);
    set.insert(30);
    set.insert(22);
    set.insert(22);
    set.insert(40);
    set.insert(1);
    set.insert(400);
    set.insert(10);

    set.has(30);
    set.has(40);
    set.has(400);

    set.remove(22);
    set.remove(3);
    set.remove(22);
  }

  @Override
  protected Node<T> find(T t) {
    Node<T> node = super.find(t); //Gets the node with that value (or null if nonexistent)
    if (node != null) { //if the node exists
      remove(node);
      Node<T> n = new Node<>(t);
      if (head != null) { //non-empty
        n.next = head; //setting it up to be the head (front)
        head.prev = n;
        head = n;
      } else { //if the only node in the list was removed
        head = n;
        tail = head;
      }
      return n;
    }
    return node; //would be null if here
  }

}
