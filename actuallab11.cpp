#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <limits> 
#include <ios>


using namespace std;


/**
 * 
 * Represents an MP3 track with its details and playback functionality.
 *
 * The MP3 class encapsulates the properties and behavior of an MP3 track,
 * including its title, artist, album, year, and lyrics. It provides methods
 * to display track details, play the track, and stop the track playback.
 *
 * The class allows creating an MP3 track by specifying its details through
 * the constructor, or by using the default constructor and setting the
 * individual properties manually.
 */
class MP3 {
public:
    /**
     * Constructs an MP3 track with the given details.
     *
     * @param newTitle The title of the MP3 track.
     * @param newArtist The artist of the MP3 track.
     * @param newAlbum The album of the MP3 track.
     * @param newYear The year of the MP3 track.
     * @param newLyrics The lyrics of the MP3 track.
     */
    string title;
    string artist;
    string album;
    int year;
    string lyrics;
    
    //TODO: Create a constructor that takes 5 parameters and assigns them to the 5 variables
    MP3(string newTitle, string newArtist, string newAlbum, int newYear, string newLyrics) : title(newTitle), artist(newArtist), album(newAlbum), year(newYear), lyrics(newLyrics) {}
    
    /**
     * Constructs an empty MP3 track with default values.
     *
     * The default constructor initializes the MP3 track with an empty title,
     * artist, album, and lyrics. The year is set to 0.
     */
    //TODO: Create this constructor
    MP3() : title(""), artist(""), album(""), year(0), lyrics("") {}
    
    /**
     * Displays the details of the MP3 track.
     *
     * This function prints the title, artist, album, year, and lyrics of the
     * MP3 track to the standard output.
     */
    void displayDetails();
    
    /**
     * Plays the MP3 track.
     *
     * This function starts playing the MP3 track by setting the isPlaying flag
     * to true and displaying the track details and lyrics. If the track is
     * already playing, it displays a message indicating that it is already
     * playing.
     */
    void play();
    
    /**
     * Stops the MP3 track.
     *
     * This function stops the playback of the MP3 track by setting the isPlaying
     * flag to false and displaying the stopped track details. If the track is
     * already stopped, it displays a message indicating that it is already
     * stopped.
     */
    void stop();

private:
    /* Flag indicating if the track is currently playing or not. */
    bool isPlaying = false;
    
    /**
     * Prints the lyrics of the MP3 track.
     *
     * This function prints the lyrics of the MP3 track to the standard output.
     */
    void printLyrics();
};

 /**
 * Displays the details of the MP3 object aside from lyrics.
 */
void MP3::displayDetails() {
    //TODO: Complete this function
    cout << "  Track Title: " << title << endl;
    cout << "  Artist: " << artist << endl;
    cout << "  Album: " << album << endl;
    cout << "  Year: " << year << endl;
}

  /**
 * Prints the lyrics of the MP3 song.
 */
void MP3::printLyrics() {
    //TODO: Complete this function
    cout << "Lyrics" << endl;
    cout << lyrics << endl;
}

/**
 * Plays the MP3 song by setting the isPlaying flag to true and displaying the song details and lyrics.
 * If the song is already playing, it displays a message indicating that it is already playing.
 */
void MP3::play() {
    //TODO: Complete this function
    if (isPlaying) {
        cout << "Track '" << title << "' by " << artist << " is playing." << endl;
    } 
    else {
        isPlaying = true;
        cout << " Now Playing:" << endl;
        displayDetails();
        printLyrics();
    }
}

/**
 * Stops the MP3 song by setting the isPlaying flag to false and displaying the stopped song details.
 * If the song is already stopped, it displays a message indicating that it is already stopped.
 */
void MP3::stop() {
    //TODO: Complete this function
    if (!isPlaying) {
        cout << "Track '" << title << "' by " << artist << " is stopped." << endl;
    } else {
        isPlaying = false;
        cout << " Playback Stopped for:" << endl;
        displayDetails();
    }
}




/**
 * Adds track details from a file to the music collection.
 * The user is prompted to enter the filename.
 * The function reads the title, artist, album, and lyrics from the file and creates an MP3 object with those details.
 * The MP3 object is then added to the musicCollection vector.
 *
 * @param musicCollection The vector representing the music collection.
 */
void addTrackFromFile(vector<MP3>& musicCollection, const string& filename="") {
    string actualFilename = filename;

    //TODO: Get the filename from the user if it isn't already a parameter
    if (actualFilename.empty()) {
        cout << "Enter the filename: ";
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); // Clear buffer before getting filename - taken from github (https://gist.github.com/DerexScript/d4220fdd40203978f8ba80c0010fa970)
        getline(cin, actualFilename);
    }

    //TODO: Open the file for reading. Report an error if it doesn't open
    ifstream inputFile(actualFilename);
    if (!inputFile.is_open()) {
        cout << " Error: Could not open file '" << actualFilename << "'" << endl;
        return;
    }

    // TODO: Read and store title, artist, and album from the file
    string title, artist, album, line;
    int year = 0;
    string lyrics;

    // Assuming Title, Artist, Album are on separate lines, and Year on its own line
    // and Lyrics follow immediately after that until EOF.
    // Use getline for strings to handle spaces.
    if (!getline(inputFile, title) || !getline(inputFile, artist) || !getline(inputFile, album)) { //if the title, artist, or album is not available in the file:
        cout << " Error: Could not read title, artist, or album from desired file '" << actualFilename << "'" << endl;
        inputFile.close();
        return;
    }

    // TODO: Read and store year from the file
    if (!(inputFile >> year)) {
        cout << " Error: Could not read year from file '" << actualFilename << "'" << endl;
        inputFile.close();
        return;
    }
    // Consume the newline character after the year
    inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    // TODO: Read and store lyrics from the file
    // Read the rest of the file into the lyrics string
    while (getline(inputFile, line)) {
        lyrics += line + "\n";
    }

    // Remove the trailing newline if it exists
    if (!lyrics.empty() && lyrics.back() == '\n') {
        lyrics.pop_back();
    }

    //TODO: Create an MP3 track and give it the stored values
    MP3 newTrack(title, artist, album, year, lyrics);

    //TODO: Put the track into the musicCollection
    musicCollection.push_back(newTrack);

    //TODO: Close the file and report success
    inputFile.close();
    cout << " Success: Added track '" << title << "' from file '" << actualFilename << "'." << endl;
}


/**
 * Searches the music collection for tracks by artist (partial matching).
 * Displays the search results (tracks) along with their details.
 * If no tracks are found for the given artist, it displays a message indicating that.
 *
 * @param musicCollection The vector representing the music collection.
 * @param artist The artist name to search for.
 */
void searchByArtist(vector<MP3>& musicCollection, string& artist) {
    cout << "\nSearch results for artist: " << artist << endl;
    bool found = false;

    for (MP3& track : musicCollection) {
        if (track.artist.find(artist) != string::npos) {
            found = true;
            track.displayDetails();
            cout << endl;
        }
    }

    if (!found) {
        cout << "No tracks found for that artist." << endl;
    }
}

void searchByTitle(vector<MP3>& musicCollection, string& title) {
    cout << "\nSearch results for title: " << title << endl;
    bool found = false;

    for (MP3& track : musicCollection) {
        if (track.title.find(title) != string::npos) {
            found = true;
            track.displayDetails();
            cout << endl;
        }
    }

    if (!found) {
        cout << "No tracks found with that title." << endl;
    }
}

void searchByLyrics(vector<MP3>& musicCollection, string& lyrics) {
    cout << "\nSearch results for lyrics containing: " << lyrics << endl;
    bool found = false;

    for (MP3& track : musicCollection) {
        if (track.lyrics.find(lyrics) != string::npos) {
            found = true;
            track.displayDetails();
            cout << endl;
        }
    }

    if (!found) {
        cout << "No tracks found with those lyrics." << endl;
    }
}


/**
 * Displays all tracks in the music collection.
 *
 * @param musicCollection The vector representing the music collection.
 */
void displayTracks(vector<MP3>& musicCollection) {
    //TODO: Complete this function
    cout << "\nCurrent Music Collection (" << musicCollection.size() << " tracks):" << endl;
    if (musicCollection.empty()) {
        cout << "The collection is empty." << endl;
        return;
    }

    for (size_t i = 0; i < musicCollection.size(); ++i) {
        cout << "[" << i << "] ";
        musicCollection[i].displayDetails();
    }
}


/**
 * Prompts the user with a menu of options and performs the corresponding actions based on user input.
 * Manages the interaction with the music collection and performs various operations such as adding tracks,
 * searching tracks, playing songs, stopping songs, and displaying track details.
 *
 * @param musicCollection The vector representing the music collection.
 */



vector<MP3> createPlaylist(vector<MP3>& musicCollection) {
    vector<MP3> playlist;

    if (musicCollection.empty()) {
        cout << "Music collection is empty. Cannot create a playlist." << endl;
        return playlist;
    }

    cout << "\nCreating a new playlist..." << endl;
    displayTracks(musicCollection);

    cout << "Enter track indices to add (-1 to finish):" << endl;

    while (true) {
        int index;
        cout << "Track index: ";
        cin >> index;

        if (index == -1)
            break;

        if (index >= 0 && index < (int)musicCollection.size()) {
            playlist.push_back(musicCollection[index]);
            cout << "Added \"" << musicCollection[index].title << "\" to playlist." << endl;
        } else {
            cout << "Invalid index." << endl;
        }
    }

    cout << "Playlist created with " << playlist.size() << " tracks." << endl;
    return playlist;
}


void startPlaylist(const vector<MP3>& playlist) {
    if (playlist.empty()) {
        cout << "Playlist is currently empty." << endl;
        return;
    }

    cout << "\nStarting playlist..." << endl;

    for (size_t i = 0; i < playlist.size(); ++i) {
        MP3 track = playlist[i];  
        cout << "\nTrack " << i << " " << endl;
        track.play();
        track.stop();
    }

    cout << "\nFinished playing playlist." << endl;
}

void displayMenu(vector<MP3>& musicCollection) {
    vector<MP3> play_list;
    int choice;
    do {
        cout << endl;
        cout << "Menu:" << endl;
        cout << "1. Add track details from a file" << endl;
        cout << "2. Search tracks by artist" << endl;
        cout << "3. Search tracks by title" << endl;
        cout << "4. Search tracks by lyrics" << endl;
        cout << "5. Display all tracks" << endl;
        cout << "6. Play a song" << endl;
        cout << "7. Stop a song" << endl;
        cout << "8. Create a playlist" << endl;
        cout << "9. Start playlist" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (!cin.good()) {
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                addTrackFromFile(musicCollection);
                break;
            case 2:
                {
                    string artist;
                    cout << "Enter the artist: ";
                    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                    getline(cin, artist);
                    searchByArtist(musicCollection, artist);
                }
                break;
            case 3:
                {
                    string title;
                    cout << "Enter the title: ";
                    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                    getline(cin, title);
                    searchByTitle(musicCollection, title);
                }
                break;
            case 4:
                {
                    string lyrics;
                    cout << "Enter the lyrics: ";
                    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                    getline(cin, lyrics);
                    searchByLyrics(musicCollection, lyrics);
                }
                break;
            case 5:
                displayTracks(musicCollection);
                break;
            case 6:
                {
                    cout << "List of tracks by index:" << endl;
                    for (size_t i = 0; i < musicCollection.size(); ++i) {
                        cout << "[" << i << "] " << musicCollection[i].title 
                             << " - " << musicCollection[i].artist << endl;
                    }

                    int trackIndex;
                    cout << "Enter the index of the song to play: ";
                    cin >> trackIndex;

                    if (trackIndex >= 0 && trackIndex < (int)musicCollection.size()) {
                        musicCollection[trackIndex].play();
                    } else {
                        cout << "Invalid index." << endl;
                    }

                }
                break;
            case 7:
                {
                    cout << "\nList of tracks by index:" << endl;
                    for (size_t i = 0; i < musicCollection.size(); ++i) {
                        cout << "[" << i << "] " << musicCollection[i].title 
                             << " - " << musicCollection[i].artist << endl;
                    }

                    int trackIndex;
                    cout << "Enter the index of the song to stop: ";
                    cin >> trackIndex;

                    if (trackIndex >= 0 && trackIndex < (int)musicCollection.size()) {
                        musicCollection[trackIndex].stop();
                    } else {
                        cout << "Invalid index." << endl;
                    }

                }
                break;
            case 8:
                play_list = createPlaylist(musicCollection);
                break;
            case 9:
                startPlaylist(play_list);
                break;

            case 10:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 10);
}

int main() {
    //TODO: Create a vector of MP3s called musicCollection
    vector<MP3> musicCollection;
    cout<< "\n" << endl;
    // Open files mp3_1.txt to mp3_9.txt
    for (int i = 1; i <= 9; ++i) {
        string filename = "mp3_" + to_string(i) + ".txt";
        //TODO: Call addTrackFromFile(musicCollection, filename);
        addTrackFromFile(musicCollection, filename);
    }

    //TODO: call displayMenu(musicCollection);
    displayMenu(musicCollection);

    return 0;
}