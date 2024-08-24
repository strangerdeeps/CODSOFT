#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// A function to calculate the cosine similarity between two users
double cosine_similarity(const vector<double>& user1, const vector<double>& user2) {
    double dot_product = 0.0, norm_user1 = 0.0, norm_user2 = 0.0;
    for (size_t i = 0; i < user1.size(); i++) {
        dot_product += user1[i] * user2[i];
        norm_user1 += user1[i] * user1[i];
        norm_user2 += user2[i] * user2[i];
    }
    return dot_product / (sqrt(norm_user1) * sqrt(norm_user2));
}

// A function to recommend movies to a user based on collaborative filtering
vector<pair<string, double>> recommend_movies(
    const vector<vector<double>>& ratings, 
    const map<int, string>& movie_names,
    int target_user
) {
    vector<double> target_ratings = ratings[target_user];
    vector<pair<int, double>> similarities;

    // Compute similarity between target user and all other users
    for (size_t i = 0; i < ratings.size(); i++) {
        if (i != target_user) {
            double sim = cosine_similarity(target_ratings, ratings[i]);
            similarities.push_back({i, sim});
        }
    }

    // Sort similarities in descending order
    sort(similarities.begin(), similarities.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    // Weighted sum of ratings to get recommendations
    map<int, double> weighted_ratings;
    map<int, double> similarity_sums;

    for (auto& sim_pair : similarities) {
        int other_user = sim_pair.first;
        double similarity = sim_pair.second;

        for (size_t j = 0; j < ratings[other_user].size(); j++) {
            if (target_ratings[j] == 0) { // If the target user hasn't rated the movie
                weighted_ratings[j] += ratings[other_user][j] * similarity;
                similarity_sums[j] += similarity;
            }
        }
    }

    vector<pair<string, double>> recommendations;
    for (auto& item : weighted_ratings) {
        int movie_id = item.first;
        double weighted_sum = item.second;

        if (similarity_sums[movie_id] != 0) {
            recommendations.push_back({movie_names.at(movie_id), weighted_sum / similarity_sums[movie_id]});
        }
    }

    // Sort recommendations by predicted rating
    sort(recommendations.begin(), recommendations.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    return recommendations;
}
int main() {
    // Example movie names (id -> name)
    map<int, string> movie_names = {
        {0, "The Matrix"},
        {1, "Inception"},
        {2, "Interstellar"},
        {3, "The Godfather"},
        {4, "The Dark Knight"},
        {5, "Pulp Fiction"}
    };

    // User ratings matrix (rows: users, columns: movies)
    vector<vector<double>> ratings = {
        {5, 4, 0, 0, 3, 0},  // User 0's ratings
        {4, 5, 4, 0, 0, 0},  // User 1's ratings
        {0, 0, 5, 4, 4, 3},  // User 2's ratings
        {5, 0, 4, 5, 0, 5},  // User 3's ratings
        {0, 4, 0, 0, 5, 4},  // User 4's ratings
    };

    // Target user for whom we want to recommend movies
    int target_user = 0;

    // Generate recommendations
    vector<pair<string, double>> recommendations = recommend_movies(ratings, movie_names, target_user);

    // Display recommendations
    cout << "Recommended movies for User " << target_user << ":\n";
    for (const auto& rec : recommendations) {
        cout << rec.first << " with predicted rating: " << rec.second << endl;
    }

    return 0;
}
