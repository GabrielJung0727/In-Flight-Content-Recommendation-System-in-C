# include <stdio.h>
# include <stdlib.h>
# include <string.h>

#define MAX_PASSENGERS 100
#define MAX_GENRES 10
#define MAX_TITLE_LENGTH 100
#define MAX_NAME_LENGTH 50
#define MAX_SEAT_LENGTH 5

typedef struct {
	char title[MAX_TITLE_LENGTH];
	char genre[MAX_NAME_LENGTH];
}
Content;

typedef struct {
	char name[MAX_NAME_LENGTH];
	char preferredGenres[MAX_GENRES][MAX_NAME_LENGTH];
    int genreCount;
}
Passenger;

typedef struct {
	char seatNumber[MAX_SEAT_LENGTH];
	Passenger passenger;
}
Seat;

typedef struct {
	char flightNumber[MAX_TITLE_LENGTH];
	Seat seats[MAX_PASSENGERS];
	int seatCount;
}
Flight;

void loadPassengers(Flight* flight);
void recommendContents(Passenger passenger, Content contents[], int contentCount);
void resetSystem();

int main()
{
	// 항공편 데이터 생성
	Flight flight;
	printf("Enter the date of the flight (YYYY-MM-DD):\n");
	char flightDate[MAX_TITLE_LENGTH];
	scanf("%s", flightDate);

	printf("Enter the flight number:\n");
	scanf("%s", flight.flightNumber);
	flight.seatCount = 0;

	loadPassengers(&flight);

	// 콘텐츠 데이터 (예시)
	Content contents[] = {
		{"Avengers: Endgame", "Action"},
		{"The Hangover", "Comedy"},
		{"The Shawshank Redemption", "Drama"},
		{"It", "Horror"},
		{"Finding Nemo", "Adventure"}
	};
	int contentCount = sizeof(contents) / sizeof(contents[0]);

	// 각 좌석의 승객에 대해 개인화된 콘텐츠 추천
	for (int i = 0; i < flight.seatCount; i++)
	{
		if (strlen(flight.seats[i].passenger.name) > 0)
		{
			printf("Recommended contents for %s at seat %s:\n", flight.seats[i].passenger.name, flight.seats[i].seatNumber);
			recommendContents(flight.seats[i].passenger, contents, contentCount);
		}
	}

	// 프로그램 종료 시 초기화
	printf("Press any key to exit and reset the system...\n");
	getchar();  // 버퍼 비우기
	getchar();  // 사용자 입력 대기
	resetSystem();

	return 0;
}

void loadPassengers(Flight* flight)
{
	FILE* file = fopen("passengers.txt", "r");
	if (file == NULL)
	{
		perror("Failed to open passengers.txt");
		exit(EXIT_FAILURE);
	}

	char line[256];
	while (fgets(line, sizeof(line), file) && flight->seatCount < MAX_PASSENGERS)
	{
		char* token = strtok(line, ";");
		if (token != NULL)
		{
			strcpy(flight->seats[flight->seatCount].passenger.name, token);
			flight->seats[flight->seatCount].passenger.genreCount = 0;

			token = strtok(NULL, "\n");
			if (token != NULL)
			{
				char* genreToken = strtok(token, ",");
				while (genreToken != NULL && flight->seats[flight->seatCount].passenger.genreCount < MAX_GENRES)
				{
					strcpy(flight->seats[flight->seatCount].passenger.preferredGenres[flight->seats[flight->seatCount].passenger.genreCount++], genreToken);
					genreToken = strtok(NULL, ",");
				}
			}

			// 좌석 번호 설정 (1A, 1B 형식)
			sprintf(flight->seats[flight->seatCount].seatNumber, "1%d", flight->seatCount + 1);
			flight->seatCount++;
		}
	}
	fclose(file);
}

void recommendContents(Passenger passenger, Content contents[], int contentCount)
{
	for (int i = 0; i < contentCount; i++)
	{
		for (int j = 0; j < passenger.genreCount; j++)
		{
			if (strcmp(contents[i].genre, passenger.preferredGenres[j]) == 0)
			{
				printf("- %s (%s)\n", contents[i].title, contents[i].genre);
			}
		}
	}
}

void resetSystem()
{
	// 시스템 초기화 로직
	printf("System reset completed.\n");
}
