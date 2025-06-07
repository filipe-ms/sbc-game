// REQUEST_H
#pragma once
#ifndef REQUEST_H
#define REQUEST_H

/**
 * @brief Initializes the underlying request system (e.g., curl global init).
 * MUST be called once before any calls to Request().
 * @return 0 on success, non-zero on failure.
 */
int InitRequestSystem();

/**
 * @brief Cleans up the underlying request system (e.g., curl global cleanup).
 * MUST be called once when the application is shutting down.
 */
void CleanupRequestSystem();

/**
 * @brief Sends a prompt to the Gemini API and returns the text response.
 * Assumes InitRequestSystem() has been called successfully.
 * The caller is responsible for freeing the returned string using FreeResponse().
 * @param prompt The text prompt to send.
 * @return Allocated string containing the response text, or NULL on failure.
 */
char* Request(char* prompt);

/**
 * @brief Frees the memory allocated for the response string returned by Request().
 * @param response The pointer returned by Request(). Does nothing if response is NULL.
 */
void FreeResponse(char* response);

//---------------------------------------

#endif // REQUEST_H