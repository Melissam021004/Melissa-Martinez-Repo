package hw4;


import exceptions.EmptyException;
import java.util.Scanner;

/**
 * A program for an RPN calculator that uses a stack.
 */
public final class Calc {
  /**
   * The main function.
   *
   * @param args Not used.
   */
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    String token = scanner.next();
    LinkedStack<Integer> integers = new LinkedStack<>();

    while (!("!".equals(token))) {
      if (isInt(token)) {
        integers.push(Integer.parseInt(token));
      } else if (isOperator(token)) {
        handleOperatorTokens(integers, token);
      } else if (".".equals(token) || "?".equals(token)) {
        handleCommands(integers,token);
      } else {
        //At this point, it is not a valid input
        System.out.println("ERROR: Invalid token.");
      }
      token = scanner.next();
    }
  }

  //Handles . and ? commands and prints error if stack is empty when . is called.
  private static void handleCommands(LinkedStack<Integer> integers, String token) {
    if (".".equals(token)) {
      if (!integers.empty()) {
        System.out.println(integers.top());
      } else {
        System.out.println("ERROR: List is empty.");
      }
    } else if ("?".equals(token)) {
      System.out.println(integers);
    }
  }

  //Ensures there's enough integers to perform operation and calls method to perform operation.
  private static void handleOperatorTokens(LinkedStack<Integer> integers, String token) {
    try {
      int b = integers.top();
      integers.pop();
      //Ensures b can be a divisor if token is / or % and that there is a second integer
      if (isValid(b, token) && !(integers.empty())) {
        int a = integers.top();
        integers.pop();
        integers.push(handleOperations(a, b, token));
      } else {
        //Cannot perform operation, put b back on stack
        integers.push(b);
        System.out.println("ERROR: Operation cannot be applied.");
      }
    } catch (EmptyException ex) {
      //Not enough integers to perform operations.
      System.out.println("ERROR: Not enough integers to execute operation.");
    }
  }

  //Ensures that division by 0 will not occur if token is / or %.
  private static boolean isValid(int b, String token) {
    if ("/".equals(token) || "%".equals(token)) {
      return !(b == 0);
    }
    return true;
  }

  //Tests token to see if it is an integer, returns true if it is.
  private static boolean isInt(String s) {
    try {
      Integer.parseInt(s);
      return true;
    } catch (NumberFormatException ex) {
      return false;
    }
  }

  //Returns true if the string passed is a valid operator
  private static boolean isOperator(String s) {
    return "+".equals(s) || "-".equals(s) || "*".equals(s) || "/".equals(s) || "%".equals(s);
  }

  //Assumes integers passed are valid for the operation passed and executes that operation.
  private static int handleOperations(int a, int b, String op) {
    switch (op) {
      case("+"):
        return a + b;
      case("-"):
        return a - b;
      case("*"):
        return a * b;
      case("/"):
        return a / b;
      case("%"):
        return a % b;
      default:
        return 0;
    }
  }
}
