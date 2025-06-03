import { z } from "zod";

export const createDeckSchema = z.object({
  title: z
    .string()
    .min(1, "Title is required")
    .max(100, "Title must be 100 characters or less"),
});

export const updateDeckSchema = createDeckSchema.partial();

export const getDeckSchema = z.object({
    id: z.coerce.number().int().positive(),
});

export const createCardSchema = z.object({
    front: z
      .string()
      .min(1, "Front content is required")
      .max(500, "Front content must be 100 characters or less"),
    back: z
      .string()
      .min(1, "Back content is required")
      .max(500, "Back content must be 100 characters or less"),
  });

  export const updateCardSchema = createCardSchema.partial();

  export const getCardsSchema = z.object({
    deckId: z.coerce.number().int().positive()
  });
  
  export const getCardSchema = z.object({
    deckId: z.coerce.number().int().positive(),
    cardId: z.coerce.number().int().positive(),
  });

  export const queryParamsSchema = z.object({
    search: z.string().optional(),
    page: z.coerce.number().int().positive().optional(),
    limit: z.coerce.number().lte(100).int().positive().optional()
  });