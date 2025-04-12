# In-Flight Content Recommendation System in C
## This C program simulates an in-flight personalized content recommendation system based on passengers' preferred genres.

- Struct Definitions
  - Content: Holds movie title and genre.
  - Passenger: Stores name and list of preferred genres.
  - Seat: Links a passenger to a seat.
  - Flight: Contains flight number and a list of seats.

- Data Loading
  - loadPassengers: Reads passengers.txt, parses each passenger’s name and genre preferences, and assigns seats.
  - Seat numbers are generated as 1A, 1B, etc.

- Content Recommendation
  - recommendContents: Recommends content matching each passenger’s genre preferences.

- System Reset
  - resetSystem: Displays a message when the system shuts down.
 
- Sample Data
<pre>
<code>
Alice;Action,Comedy
Bob;Drama,Horror
Charlie;Comedy,Adventure
</code>
</pre>

> Based on this, the system prints recommended movies for each passenger to the console.
