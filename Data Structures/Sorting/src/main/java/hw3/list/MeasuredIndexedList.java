package hw3.list;

import exceptions.IndexException;

/**
 * An ArrayIndexedList that is able to report the number of
 * accesses and mutations, as well as reset those statistics.
 *
 * @param <T> The type of the array.
 */
public class MeasuredIndexedList<T> extends ArrayIndexedList<T>
    implements Measured<T> {

  int numAccesses;
  int numMutations;
  /**
   * Constructor for a MeasuredIndexedList.
   *
   * @param size         The size of the array.
   * @param defaultValue The initial value to set every object to in the array.
   */

  public MeasuredIndexedList(int size, T defaultValue) {
    super(size, defaultValue);
    numAccesses = 0;
    numMutations = 0;
  }

  @Override
  public int length() {
    return super.length();
  }

  @Override
  public T get(int index) throws IndexException {
    T temp = super.get(index);
    //Should throw an Index Exception by here if invalid and not update the rest
    numAccesses++;
    return temp;
  }

  @Override
  public void put(int index, T value) throws IndexException {
    super.put(index, value);
    //Should throw an exception here if invalid, mutations won't get updated
    numMutations++;
  }

  @Override
  public void reset() {
    numMutations = 0;
    numAccesses = 0;
  }

  @Override
  public int accesses() {
    return numAccesses;
  }

  @Override
  public int mutations() {
    return numMutations;
  }

  @Override
  public int count(T value) {
    int count = 0;
    for (int i = 0; i < super.length(); i++) {
      if (super.get(i) == value) {
        count++;
      }
      numAccesses++;
    }
    return count;
  }

}
