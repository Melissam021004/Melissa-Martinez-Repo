package hw5;

/**
 * Set implemented using plain Java arrays and transpose-sequential-search heuristic.
 *
 * @param <T> Element type.
 */
public class TransposeArraySet<T> extends ArraySet<T> {

  /**
   * Runs a TransposeArraySet and its methods to ensure correct function.
   * @param args Is the main method
   */
  public static void main(String[] args) {
    TransposeArraySet<Integer> set = new TransposeArraySet<>();
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

    set.remove(3);
    set.remove(3);
    set.remove(6);
  }

  @Override
  protected int find(T t) {
    int i = super.find(t); //Finds index of value t
    if (i > 0) { //Making sure it's an index that can be switched
      T temp = data[i]; //Initiate swap
      data[i] = data[i - 1];
      data[i - 1] = temp;
      return i - 1; //New index of the item after switching
    }
    return i; // Only if nonexistent or the first element
  }

}
