#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for events
typedef struct Event {
    char name[100];
    char start_date[9]; // Format: DDMMYYYY
    char end_date[9];   // Format: DDMMYYYY
    int priority;
} Event;

// Function prototypes
void addEvent(Event events[], int *eventCount);
void removeEvent(Event events[], int *eventCount);
void viewEvents(Event events[], int eventCount);
void sortEventsByPriority(Event events[], int eventCount);
void filterEvents(Event events[], int eventCount);

int main() {
    Event events[100]; // Array to store events
    int eventCount = 0; // Count of events
    int choice;

    while (1) {
        printf("\nEvent Scheduler Menu:\n");
        printf("1. Add Event\n");
        printf("2. Remove Event\n");
        printf("3. View Events\n");
        printf("4. Filter Events\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume the newline character after the choice

        switch (choice) {
            case 1:
                addEvent(events, &eventCount);
                break;
            case 2:
                removeEvent(events, &eventCount);
                break;
            case 3:
                viewEvents(events, eventCount);
                break;
            case 4:
                filterEvents(events, eventCount);
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to add an event
void addEvent(Event events[], int *eventCount) {
    char name[100], start_date[9], end_date[9];
    int priority;

    printf("Enter event name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove the newline character

    // Check for duplicate event name
    for (int i = 0; i < *eventCount; i++) {
        if (strcmp(events[i].name, name) == 0) {
            printf("Error: Event '%s' already exists!\n", name);
            return;
        }
    }

    printf("Enter start date (DDMMYYYY): ");
    scanf("%8s", start_date);

    printf("Enter end date (DDMMYYYY): ");
    scanf("%8s", end_date);

    printf("Enter priority (lower value = higher priority): ");
    scanf("%d", &priority);
    getchar(); // Consume the newline character

    // Add the new event to the array
    strcpy(events[*eventCount].name, name);
    strcpy(events[*eventCount].start_date, start_date);
    strcpy(events[*eventCount].end_date, end_date);
    events[*eventCount].priority = priority;

    (*eventCount)++;
    sortEventsByPriority(events, *eventCount);
    printf("Event '%s' added successfully!\n", name);
}

// Function to remove an event
void removeEvent(Event events[], int *eventCount) {
    char name[100];

    printf("Enter event name to remove: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove the newline character

    for (int i = 0; i < *eventCount; i++) {
        if (strcmp(events[i].name, name) == 0) {
            // Shift the array to remove the event
            for (int j = i; j < *eventCount - 1; j++) {
                events[j] = events[j + 1];
            }
            (*eventCount)--;
            printf("Event '%s' removed.\n", name);
            return;
        }
    }

    printf("Error: Event '%s' not found!\n", name);
}

// Function to view all events
void viewEvents(Event events[], int eventCount) {
    if (eventCount == 0) {
        printf("No events scheduled.\n");
        return;
    }

    printf("Scheduled Events:\n");
    for (int i = 0; i < eventCount; i++) {
        printf("Name: %s, Start: %s, End: %s, Priority: %d\n",
            events[i].name, events[i].start_date, events[i].end_date, events[i].priority);
    }
}

// Function to filter events based on a user-defined condition
void filterEvents(Event events[], int eventCount) {
    int filterChoice;
    printf("\nFilter Options:\n");
    printf("1. Filter by Date\n");
    printf("2. Filter by Priority\n");
    printf("Enter your choice: ");
    scanf("%d", &filterChoice);
    getchar(); // To consume the newline character

    if (filterChoice == 1) {
        char filterDate[9];
        printf("Enter the date to filter events (DDMMYYYY): ");
        scanf("%8s", filterDate);
        printf("Events on %s:\n", filterDate);

        for (int i = 0; i < eventCount; i++) {
            if (strcmp(events[i].start_date, filterDate) == 0 || strcmp(events[i].end_date, filterDate) == 0) {
                printf("Name: %s, Start: %s, End: %s, Priority: %d\n", events[i].name, events[i].start_date, events[i].end_date, events[i].priority);
            }
        }
    } else if (filterChoice == 2) {
        int filterPriority;
        printf("Enter priority value to filter events (lower value = higher priority): ");
        scanf("%d", &filterPriority);

        printf("Events with priority %d:\n", filterPriority);
        for (int i = 0; i < eventCount; i++) {
            if (events[i].priority == filterPriority) {
                printf("Name: %s, Start: %s, End: %s, Priority: %d\n", events[i].name, events[i].start_date, events[i].end_date, events[i].priority);
            }
        }
    } else {
        printf("Invalid filter choice.\n");
    }
}

// Function to sort events by priority
void sortEventsByPriority(Event events[], int eventCount) {
    for (int i = 0; i < eventCount - 1; i++) {
        for (int j = i + 1; j < eventCount; j++) {
            if (events[i].priority > events[j].priority) {
                Event temp = events[i];
                events[i] = events[j];
                events[j] = temp;
            }
        }
    }
}
