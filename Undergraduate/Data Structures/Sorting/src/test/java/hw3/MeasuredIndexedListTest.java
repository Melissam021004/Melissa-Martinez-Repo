package hw3;

import exceptions.IndexException;
import hw3.list.MeasuredIndexedList;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import java.util.Iterator;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class MeasuredIndexedListTest {

  private static final int LENGTH = 15;
  private static final int DEFAULT_VALUE = 3;

  private MeasuredIndexedList<Integer> measuredIndexedList;

  @BeforeEach
  void setup() {
    measuredIndexedList = new MeasuredIndexedList<>(LENGTH, DEFAULT_VALUE);
  }

  @Test
  @DisplayName("MeasuredIndexedList starts with zero reads")
  void zeroReadsStart() {
    assertEquals(0, measuredIndexedList.accesses());
  }

  @Test
  @DisplayName("MeasuredIndexedList starts with zero writes")
  void zeroWritesStart() {
    assertEquals(0, measuredIndexedList.mutations());
  }

  @Test
  @DisplayName(("The number of mutations is correctly recorded and other variables are unchanged."))
  void MutationsCountTest() {
    for(int i = 0; i < 15; i++){
      measuredIndexedList.put(i, i);
    }
    assertEquals(15, measuredIndexedList.mutations());
    assertEquals(0, measuredIndexedList.accesses());
    assertEquals(15, measuredIndexedList.length());
  }

  @Test
  @DisplayName("Number of accesses is correctly recorded and other variables are unchanged.")
  void AccessesCountTest(){
    int temp = 0;
    for(int i = 0; i < 15; i++){
      temp = measuredIndexedList.get(i);
    }
    assertEquals(3, temp);
    assertEquals(0, measuredIndexedList.mutations());
    assertEquals(15, measuredIndexedList.accesses());
    assertEquals(15, measuredIndexedList.length());
  }

  @Test
  @DisplayName("Count method works properly")
  void CountTest(){
    for(int i = 0; i < 15; i++){
      measuredIndexedList.put(i, i % 3);
    }
    assertEquals(5, measuredIndexedList.count(0));
    assertEquals(5, measuredIndexedList.count(1));
    assertEquals(5, measuredIndexedList.count(2));
  }

  @Test
  @DisplayName("Restart method works properly")
  void RestartTest(){
    int temp = 0;
    for(int i = 0; i < 15; i++){
      temp = measuredIndexedList.get(i);
      measuredIndexedList.put(i, i);
    }

    assertEquals(3, temp);
    assertEquals(15, measuredIndexedList.mutations());
    assertEquals(15, measuredIndexedList.accesses());
    assertEquals(15, measuredIndexedList.length());
    measuredIndexedList.reset();
    assertEquals(0, measuredIndexedList.accesses());
    assertEquals(0, measuredIndexedList.mutations());
    assertEquals(15, measuredIndexedList.length());
  }

  @Test
  @DisplayName("Accessor aren't updated if invalid index")
  void noAccessorVariableUpdate(){
    try {
      measuredIndexedList.get(20);
    } catch(IndexException ex) {
      assertEquals(0, measuredIndexedList.accesses());
    }
  }

  @Test
  @DisplayName("Variables aren't updated if invalid index")
  void noMutationsVariableUpdate(){
    try {
      measuredIndexedList.put(20, 20);
    } catch(IndexException ex) {
      assertEquals(0, measuredIndexedList.mutations());
    }
  }

  @Test
  @DisplayName("Iterating does not change values")
  void iteratorNoChange(){
    Iterator<Integer> it = measuredIndexedList.iterator();
    int count = 0;
    while(it.hasNext()){
      assertEquals(it.next(), 3);
      count++;
    }
    assertEquals(15, count);
    assertEquals(0, measuredIndexedList.mutations());
    assertEquals(0, measuredIndexedList.accesses());
    assertEquals(15, measuredIndexedList.length());
  }
}
