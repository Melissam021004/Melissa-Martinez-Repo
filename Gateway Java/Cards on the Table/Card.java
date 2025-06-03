/**
 * Project 5A
 * Card class creates a card with a certain rank and suit. 
 * Melissa Martinez D4E3E5 April 13, 2023
 */
public class Card {

   private int suit;
   private int rank;
   private String[] allSuits = {"Clubs", "Diamonds", "Hearts", "Spades"};
   private String[] allRanks = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9",
      "10", "Jack", "Queen", "King"};
   
   /**
    * Creates a new card with a certain rank and suit.
    * @param r Rank of the card
    * @param s Suit of the card
    */
   public Card(int r, int s) {
      if (r > 0 && r < 14 && s > 0 && s < 5) {
         suit = s;
         rank = r;
      }
      else {
         suit = 0;
         rank = 0;
      }
   }
   
   /**
    * Returns the suit of the card.
    * @return integer value of the suit
    */
   public int getSuit() {
      return suit;
   }
   
   
   /**
    * Returns the rank of the card.
    * @return integer value of the rank
    */
   public int getRank() {
      return rank;
   }
   
   /**
    * Converts the card to a string format.
    * @return Card in [rank] of [suit] format
    */
   @Override
   public String toString() {
      if (suit == 0 && rank == 0) {
         return "Invalid card.";
      }
      else {
         return allRanks[rank - 1] + " of " + allSuits[suit - 1];
      }
   }
   
   /**
    * Compares two cards and returns true if equal.
    * @return true if suit and rank are the same
    */
   @Override  
   public boolean equals(Object other) {
      Card t = (Card) other;
      boolean equal = false;
      if (rank == t.getRank() && suit == t.getSuit()) {
         
         equal = true;
         
      }
      return equal;
   }
   
   /**
    * Compare this Card with the specified otherCard for order.
    * @param otherCard the other Card object to be compared.
    * @return a negative integer, zero, or a positive integer as
    * this object is less than, equal to, or greater than the otherCard.
    */
   public int compareTo(Card otherCard) {
      int suitLoc = otherCard.getSuit();
      int rankLoc = otherCard.getRank();
      
      if (suitLoc == suit && rankLoc == rank) {
         return 0;
      }
      else if (suit < suitLoc) {
         return -1;
      }
      else if (suitLoc < suit) {
         return 1;
      }
      else if (rank < rankLoc) {
         return -1;
      }
      else {
         return 1;
      }
      
   }
   
   
   
}