# -*- coding: utf-8 -*-
"""RANDOM FOREST LABEL AND ONEHOT ENCODER.ipynb

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/1xx6oKgrIK5XYcC9htXJ-qw9f7DxBvlYK

**Import necessary libraries**
"""

from google.colab import drive
drive.mount('/content/drive')

import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.tree import plot_tree
from sklearn.preprocessing import LabelEncoder, OneHotEncoder
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
from sklearn.compose import ColumnTransformer

"""**Load the dataset**"""

# Assuming the dataset is in a CSV file named 'PlayTennis.csv'
df = pd.read_csv('/content/drive/MyDrive/Colab Notebooks/Play Tennis.csv', index_col=0)

"""**Dataset Visualization**"""

df.head()

df.shape

"""**EDA**"""

ax = plt.subplots(figsize = (4,4))
ax = sns.countplot(x=df['Outlook'])
plt.show()

ax = plt.subplots(figsize = (4,4))
ax = sns.countplot(x=df['Temprature'])
plt.show()

ax = plt.subplots(figsize = (4,4))
ax = sns.countplot(x=df['Humidity'])
plt.show()

ax = plt.subplots(figsize = (4,4))
ax = sns.countplot(x=df['Wind'])
plt.show()

"""**Feature Extraction**"""

# Separate features (X) and target variable (y)
X = df.iloc[:, :-1]  # All columns except the last one
y = df.iloc[:, -1]   # The last column 'PlayTennis'

"""**Use OneHotEncoder for categorical variables in features**"""

categorical_features = ['Outlook', 'Temprature', 'Humidity', 'Wind']

preprocessor = ColumnTransformer(
    transformers=[
        ('encoder', OneHotEncoder(), categorical_features)
    ],
    remainder='passthrough'
)

X_encoded = preprocessor.fit_transform(X)

"""**Use LabelEncoder for the target variable**"""

label_encoder = LabelEncoder()
y_encoded = label_encoder.fit_transform(y)

"""**Split the dataset into training and testing sets**"""

X_train, X_test, y_train, y_test = train_test_split(X_encoded, y_encoded, test_size=0.2, random_state=42)

"""**Create a Random Forest classifier**"""

rf_classifier = RandomForestClassifier(n_estimators=50)

"""**Fit the model to the training data**"""

rf_classifier.fit(X_train, y_train)

"""**Make predictions on the test set**"""

y_pred = rf_classifier.predict(X_test)

"""**Evaluate the performance of the classifier**"""

accuracy = accuracy_score(y_test, y_pred)
conf_matrix = confusion_matrix(y_test, y_pred)
classification_report_str = classification_report(y_test, y_pred)

"""**Print the results**"""

print(f'RF Accuracy: {accuracy}')
print(f'RF Confusion Matrix:\n{conf_matrix}')
sns.set(rc={'figure.figsize':(6,3)})
sns.heatmap(confusion_matrix(y_test,y_pred),annot = True,fmt = 'd')
plt.xlabel('Predicted Labels')
plt.ylabel('Actual Labels')
print(f'RF Classification Report:\n{classification_report_str}')

"""**Predict whether a person will play tennis or not**"""

# Assuming we have a new set of feature values for prediction
new_data = pd.DataFrame({'Outlook': ['Sunny'], 'Temprature': ['Hot'], 'Humidity': ['High'], 'Wind': ['Weak']})

# Encode categorical variables using the same OneHotEncoder
new_data_encoded = preprocessor.transform(new_data)

# Use the trained DT model to make predictions
predicted_play_tennis = rf_classifier.predict(new_data_encoded)

# Print the predicted outcome
if predicted_play_tennis[0] == 1:
    print("The person is predicted to play tennis.")
else:
    print("The person is predicted not to play tennis.")

