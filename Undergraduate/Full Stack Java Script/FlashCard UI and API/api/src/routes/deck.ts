import { Hono } from "hono";
import { decks } from "../db/schema";
import { db } from "../db";
import { count, eq, like } from "drizzle-orm";
import { createDeckSchema, getDeckSchema, queryParamsSchema, updateDeckSchema } from "../validators/schemas";
import { zValidator } from "@hono/zod-validator";
import { HTTPException } from "hono/http-exception";

const deckRoutes = new Hono();

deckRoutes.get("/decks", 
  zValidator("query", queryParamsSchema),
  async (c) => {  
    const search = c.req.query("search");
    const page = parseInt(c.req.query("page") || "1");
    const limit = parseInt(c.req.query("limit") || "20");

    const whereClause = search
      ? like(decks.title, `%${search}%`)
      : undefined;

    const offset = (page - 1) * limit;

    const [allPosts, [{ totalCount }]] = await Promise.all([
      db
        .select()
        .from(decks)
        .where(whereClause)
        .limit(limit)
        .offset(offset),
      db
        .select({ totalCount: count() })
        .from(decks)
        .where(whereClause)
    ]);

  return c.json({
    posts: allPosts,
    page,
    limit,
    total: totalCount
  });
});

deckRoutes.get("/decks/:id", 
  zValidator("param", getDeckSchema),
  async (c) => {
    const {id} = c.req.valid("param");
    const deck = await db.select().from(decks).where(eq(decks.id, id)).get();
    if (!deck) {
      throw new HTTPException(404, {message: "Deck not found"});
    }
    return c.json(deck);

  });

deckRoutes.delete("/decks/:id", 
  zValidator("param", getDeckSchema),
  async (c) => {
    const {id} = c.req.valid("param");
    const deletedDeck = await db.delete(decks).where(eq(decks.id, id)).returning().get();
    if (!deletedDeck) {
      throw new HTTPException(404, {message: "Deck not found"});
    }
    return c.json(deletedDeck);
  });

deckRoutes.post("/decks", 
  zValidator("json", createDeckSchema),
  async (c) => {
    const { title } = c.req.valid("json");
    const newDeck = await db
        .insert(decks)
        .values({
          title,
          numberOfCards: 0,
        })
        .returning()
        .get();
    return c.json(newDeck, 201);
  });

deckRoutes.patch("/decks/:id", 
  zValidator("json", updateDeckSchema),
  zValidator("param", getDeckSchema),
  async (c) => {
    const {id} = c.req.valid("param");
    const { title } = c.req.valid("json");
    const updatedDeck = await db.update(decks).set({ title }).where(eq(decks.id, id)).returning().get();
    if (!updatedDeck) {
      throw new HTTPException(404, {message: "Deck not found"});
    }
    return c.json(updatedDeck);
  });

export default deckRoutes;