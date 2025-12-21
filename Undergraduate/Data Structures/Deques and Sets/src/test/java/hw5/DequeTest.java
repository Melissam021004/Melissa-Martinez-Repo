package hw5;

import exceptions.EmptyException;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public abstract class DequeTest {

  private Deque<String> deque;

  @BeforeEach
  public void setUp() {
    this.deque = createDeque();
  }

  protected abstract Deque<String> createDeque();

  @Test
  @DisplayName("Deque is empty after construction.")
  public void testConstructor() {
    assertTrue(deque.empty());
    assertEquals(0, deque.length());
  }

  @Test
  @DisplayName("Deque acts like stack.")
  public void testDequeActsLikeStack(){
    deque.insertBack("a");
    assertEquals(1, deque.length());
    assertEquals("a", deque.back());

    deque.insertBack("b");
    assertEquals(2, deque.length());
    assertEquals("b", deque.back());

    deque.insertBack("c");
    assertEquals(3, deque.length());
    assertEquals("c", deque.back());

    deque.removeBack();
    assertEquals(2, deque.length());
    assertEquals("b", deque.back());

    deque.removeBack();
    assertEquals(1, deque.length());
    assertEquals("a", deque.back());

    deque.removeBack();
    assertEquals(0, deque.length());
  }

  @Test
  @DisplayName("Elements inserted to the back correctly")
  public void testInsertBack() {
    deque.insertBack("a");
    assertEquals(1, deque.length());
    assertEquals("a", deque.back());
    deque.insertBack("b");
    assertEquals(2, deque.length());
    assertEquals("b", deque.back());
    deque.insertFront("c");
    assertEquals(3, deque.length());
    assertEquals("b", deque.back());
  }

  @Test
  @DisplayName("ELements inserted to the front correctly")
  public void testInsertFront() {
    deque.insertFront("a");
    assertEquals("a", deque.front());
    assertEquals(1, deque.length());
    deque.insertFront("b");
    assertEquals("b", deque.front());
    assertEquals(2, deque.length());
    deque.insertBack("c");
    assertEquals("b", deque.front());
    assertEquals(3, deque.length());
  }

  @Test
  @DisplayName("Back() returns expected value")
  public void testBackAccess(){
    deque.insertBack("a");
    assertEquals("a", deque.back());
    deque.insertBack("b");
    assertEquals("b", deque.back());
    deque.insertBack("c");
    assertEquals("c", deque.back());
    deque.insertBack("d");
    assertEquals("d", deque.back());
  }

  @Test
  @DisplayName("Front() returns expected value")
  public void testFrontAccess(){
    deque.insertFront("a");
    assertEquals("a", deque.front());
    deque.insertFront("b");
    assertEquals("b", deque.front());
    deque.insertFront("c");
    assertEquals("c", deque.front());
    deque.insertFront("d");
    assertEquals("d", deque.front());
  }

  @Test
  @DisplayName("RemoveBack() removes elements correctly ")
  public void testRemoveBack(){
    deque.insertBack("a");
    deque.insertBack("b");
    deque.insertBack("c");
    deque.insertBack("d");

    assertEquals(4, deque.length());
    assertEquals("d", deque.back());
    deque.removeBack();

    assertEquals(3, deque.length());
    assertEquals("c", deque.back());
    deque.removeBack();

    assertEquals(2, deque.length());
    assertEquals("b", deque.back());
    deque.removeBack();

    assertEquals(1, deque.length());
    assertEquals("a", deque.back());
    deque.removeBack();

    assertTrue(deque.empty());
    assertEquals(0, deque.length());
  }

  @Test
  @DisplayName("RemoveFront removes elements correctly")
  public void testRemoveFront(){
    deque.insertFront("a");
    deque.insertFront("b");
    deque.insertFront("c");
    deque.insertFront("d");

    assertEquals(4, deque.length());
    assertEquals("d", deque.front());
    deque.removeFront();

    assertEquals(3, deque.length());
    assertEquals("c", deque.front());
    deque.removeFront();

    assertEquals(2, deque.length());
    assertEquals("b", deque.front());
    deque.removeFront();

    assertEquals(1, deque.length());
    assertEquals("a", deque.front());
    deque.removeFront();

    assertTrue(deque.empty());
    assertEquals(0, deque.length());
  }

  @Test
  @DisplayName("Tests if empty() returns true when appropriate")
  public void testEmpty(){
    assertTrue(deque.empty());
    deque.insertBack("hi");
    assertFalse(deque.empty());
    deque.removeBack();
    assertTrue(deque.empty());
  }

  @Test
  @DisplayName("Length of the deque is updated correctly")
  public void testLength(){
    assertEquals(0, deque.length());
    deque.insertFront("hi");
    assertEquals(1, deque.length());
    deque.insertFront("hii");
    assertEquals(2, deque.length());
    deque.insertBack("hola");
    assertEquals(3, deque.length());
    deque.removeBack();
    assertEquals(2, deque.length());
    deque.removeBack();
    assertEquals(1, deque.length());
  }

  @Test
  @DisplayName("removeBack() method throws Empty Exception when deque is empty")
  public void testRemoveBackEmptyException() {
    try{
      deque.removeBack();
      fail();
    } catch (EmptyException ex){
      //Passed
    }
  }

  @Test
  @DisplayName("removeFront() method throws Empty Exception when deque is empty")
  public void testRemoveFrontEmptyException() {
    try{
      deque.removeFront();
      fail();
    } catch (EmptyException ex){
      //Passed
    }
  }

  @Test
  @DisplayName("back() method throws Empty Exception when deque is empty")
  public void testBackEmptyException() {
    try{
      deque.back();
      fail();
    } catch (EmptyException ex){
      //Passed
    }
  }

  @Test
  @DisplayName("front() method throws Empty Exception when deque is empty")
  public void testFrontEmptyException() {
    try{
      deque.front();
      fail();
    } catch (EmptyException ex){
      //Passed
    }
  }
  // TODO Add more tests

}
