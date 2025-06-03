## Melissa Martinez mmart213 D4E3E5

import pandas as pd
import math
import matplotlib.pyplot as plt
import numpy as np


"""
Function: prob_wins: Determines the probability of the first player winning

Arguments:
    ratA: Current rating of player A
    ratB: Current rating of player B

Returns:
    prob: The probability of the first player winning
"""
def prob_wins(ratA, ratB):
    prob = (pow(math.e, (ratA - ratB)/100))/(1 + pow(math.e, (ratA - ratB)/100))
    
    return prob

"""
Function: calculate_ratings: Calculates the ratings of all players based on csv file

Arguments:
    past_matches: the name of the file name containing the information for past matches

Returns:
    players: a dictionary of players(keys) and their ratings(values) based on past matches
"""
def calculate_ratings(past_matches):
    
    players = {0:1500, 1:1500, 2:1500, 3:1500, 4:1500, 5:1500, 6:1500, 7:1500}
    
    
    try: 
        df = pd.read_csv(past_matches, index_col=0)
        
        for index, row in df.iterrows():
            pA = row['player_A']
            pB = row['player_B']
            win = row['winner']
            
            probA = prob_wins(players[pA], players[pB])
            probB = 1 - probA
            
            if win == pA:
                players[pA] = players[pA] + 5 * (1.0 - probA)
                players[pB] = players[pB] + 5 * (0.0 - probB)
            
            elif win == pB:
                players[pA] = players[pA] + 5 * (0.0 - probA)
                players[pB] = players[pB] + 5 * (1.0 - probB)
            
        
    except FileNotFoundError:
        print("File " + past_matches + " does not exist")
    
    except:
        print("Unknown error while accessing data in " + past_matches)
        
    return players

"""
Function: display_ratings: Displays player ratings in a bar graph on screen and to barplot.pdf

Arguments:
    players: dictionary of players(key) and their rating(value)

Returns: N/A but displays a bar graph to the screen
    
"""
def display_ratings(players):
    
    plt.rc('font', family='serif')
    plt.figure(figsize=(6,6))
    plays = ['0','1','2','3','4', '5', '6', '7']
    ratings = [players[0], players[1], players[2], players[3], players[4], players[5], players[6], players[7]]
    
    plt.ylabel('Rating', fontsize=24)
    plt.xlabel('Player', fontsize = 24)
    plt.ylim(1400,1700)
    plt.xticks(fontsize=24)
    plt.yticks([i*100 + 1400 for i in range(4)], fontsize=24)
    
    plt.bar(plays, ratings)
    plt.tight_layout()
    plt.show()
    plt.savefig('projections.pdf')

"""
Function: project_win_probs: runs the game simulation 100 times and calculates probability of each player winning

Arguments:
    players: dictionary of players(key) and their ratings(value)

Returns:
    probs: dictionary of players(key) and their probability of winning the whole game (value) after 100 matches
    
"""
def project_win_probs (players):
    
    round_1_winners = []
    round_2_winners = []
    probs = {0:0.0, 1:0.0, 2:0.0, 3:0.0, 4:0.0, 5:0.0, 6:0.0, 7:0.0}
    
    for r in range (100):
        
        #Round 1
        for i in range (4):
            if np.random.rand() < prob_wins(players[i], players[7-i]):
                round_1_winners.append(i)
            else:
                round_1_winners.append(7-i)


        #Round 2
        for i in range(2):
            if np.random.rand() < prob_wins(players[round_1_winners[2*i]], players[round_1_winners[2*i + 1]]):
                round_2_winners.append(round_1_winners[2*i])
            else:
                round_2_winners.append(round_1_winners[2*i + 1])
                

        #Final Round
        if np.random.rand() < prob_wins(players[round_2_winners[0]], players[round_2_winners[1]]):
            probs[round_2_winners[0]] += 0.01
        else:
            probs[round_2_winners[1]] += 0.01
            

        round_1_winners.clear()
        round_2_winners.clear()
        
    for i in range(8):
        probs[i] = round(probs[i],2)
    
    return probs

"""
Function: display_probs: creates a csv file 'probs.csv' and a pie graph in a pdf 'projections_pie.pdf' showcasing the probability of the players winning after 100 games

Arguments:
    players: dictionary of players(key) and their probability of winning the entire game (value)

Returns: N/A but displays a pie chart to the screen
    
"""        
def display_probs (players):
    
    sorted_players = dict(sorted(players.items(), key=lambda x:x[1]))

    #Creating the csv file
    my_dict = {}
    my_dict['Player'] = reversed(list(sorted_players.keys()))
    my_dict['Ratings'] = reversed(list(sorted_players.values()))
        
    dfr = pd.DataFrame(my_dict, index = range(8))
    dfr.to_csv('probs.csv')
    
    #Creating the pie chart
    labels = ['0','1','2','3','4', '5', '6', '7']
    sizes = [players[0], players[1], players[2], players[3], players[4], players[5], players[6], players[7]]

    fig1, ax1 = plt.subplots()
    ax1.pie(sizes, labels=labels, autopct='%1.1f%%', shadow=True, startangle=90)
    ax1.axis('equal')

    plt.show()
    plt.savefig('projections_pie.pdf')
    
ratings = calculate_ratings("past_matches.csv")
display_ratings(ratings)
display_probs(project_win_probs(ratings))