-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";
    --Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
SELECT transcript FROM interviews WHERE month = 7 AND day = 28;
    --Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame. - hint for accomplice
    --I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
    --As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. - accomplice bought the ticket

SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE account_number IN (SELECT  account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw");
    --Ernest
    --Russell
    --Roy
    --Bobby
    --Elizabeth
    --Danielle
    --Madison
    --Victoria

SELECT name FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit";
    --Patrick
    --Ernest
    --Amber
    --Danielle
    --Roger
    --Elizabeth
    --Russell
    --Evelyn

-- get repeated names (suspects)

    --Ernest
    --Danielle
    --Elizabeth
    --Russell

SELECT flights.id, destination_airport_id,hour FROM flights JOIN airports ON flights.origin_airport_id = airports.id WHERE month = 7 AND day = 29 AND city = "Fiftyville" ORDER BY hour;
    --36|4|8    - earliest flight with dest id 4
    --43|1|9
    --23|11|12
    --53|9|15
    --18|6|16

SELECT name FROM people JOIN passengers ON people.passport_number = passengers.passport_number WHERE flight_id = 36 AND name IN (SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE account_number IN (SELECT  account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw")) AND name IN (SELECT name FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit");
    --Ernest
    --Danielle - two suspects left

SELECT name, receiver, duration FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE month = 7 AND day = 28 AND (name = "Ernest" OR name = "Danielle");
SELECT caller FROM phone_calls JOIN people WHERE month = 7 AND day = 28 AND (name = "Ernest" OR name = "Danielle");
    --Ernest|(375) 555-8161|45  - NOTE: thief is Ernest
    --Ernest|(344) 555-9601|120
    --Ernest|(022) 555-4052|241
    --Ernest|(704) 555-5790|75

SELECT city FROM airports WHERE id = 4;
    --London    - NOTE: thief escaped to London

SELECT name FROM people WHERE phone_number = "(375) 555-8161";
    --Berthold -- NOTE: accomplice is Berthold