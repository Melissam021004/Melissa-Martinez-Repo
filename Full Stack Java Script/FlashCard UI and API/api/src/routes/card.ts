import { and, eq } from "drizzle-orm";
import { Hono } from "hono";
import { db } from "../db";
import { cards } from "../db/schema";
import { zValidator } from "@hono/zod-validator";
import { createCardSchema, getCardSchema, getCardsSchema, queryParamsSchema, updateCardSchema } from "../validators/schemas";
import { HTTPException } from "hono/http-exception";

const cardRoutes = new Hono();

cardRoutes.get("/decks/:deckId/cards",
    zValidator("param", getCardsSchema),
    zValidator("query", queryParamsSchema),
    async (c) => {
        const { deckId } = c.req.valid("param");

        const allCards = await db.select().from(cards).where(eq(cards.deckId, deckId));

        return c.json({allCards});
    },
);

cardRoutes.get("/decks/:deckId/cards/:cardId",
    zValidator("param", getCardSchema),
    async (c) => {
      const { deckId, cardId } = c.req.valid("param");
      const card = await db
        .select()
        .from(cards)
        .where(and(eq(cards.id, cardId), eq(cards.deckId, deckId)))
        .get();
      if (!card) {
        throw new HTTPException(404, { message: "Card not found" });
      }
      return c.json(card);
    },
);

cardRoutes.delete(
    "/decks/:deckId/cards/:cardId",
    zValidator("param", getCardSchema),
    async (c) => {
      const { deckId, cardId } = c.req.valid("param");
      const deletedCard = await db
        .delete(cards)
        .where(and(eq(cards.id, cardId), eq(cards.deckId, deckId)))
        .returning()
        .get();
      if (!deletedCard) {
        throw new HTTPException(404, { message: "Card not found" });
      }
      return c.json(deletedCard);
    },
);

cardRoutes.post(
    "/decks/:deckId/cards",
    zValidator("param", getCardsSchema),
    zValidator("json", createCardSchema),
    async (c) => {
      const { deckId } = c.req.valid("param");
      const { front } = c.req.valid("json");
      const { back } = c.req.valid("json");
      
      const newCard = await db
        .insert(cards)
        .values({
          front,
          back,
          deckId
        })
        .returning()
        .get();

      if(!newCard){
        throw new HTTPException(404, {message: "Deck not found"});
      }

      return c.json(newCard);
    },
);

cardRoutes.patch(
    "/decks/:deckId/cards/:cardId",
    zValidator("param", getCardSchema),
    zValidator("json", updateCardSchema),
    async (c) => {
      const { deckId, cardId } = c.req.valid("param");
      const { front } = c.req.valid("json");
      const { back } = c.req.valid("json");
      const updatedCard = await db
        .update(cards)
        .set({ front, back })
        .where(and(eq(cards.id, cardId), eq(cards.deckId, deckId)))
        .returning()
        .get();
  
      if (!updatedCard) {
        throw new HTTPException(404, { message: "Card not found" });
      }
      return c.json(updatedCard);
    },
  );

export default cardRoutes;