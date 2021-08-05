# Wine Analytics

Determines the quality of the wine given certain factors such as volatile and citrus acidity, sugar, density, pH, alcohol level etc. These characteristics are considered for two types of wine, the first being white wine and the second red.

## Network Architect
The architecture is composed of 12 inputs, one of them being the bias, 12 elements in the first hidden layer, one of them being the bias and an output, referring to the quality of the wine.

![cnn_network](./network.jpg)

## Classification
It is the wine quality rating, ranging from 0 to 10, where 0 would be a very bad wine and 10 would be a very good wine.

## Selection Criteria
Although the wine quality values ​​ranged from 0 to 10 where 0 would be a very bad wine and 10 would be a very good wine, a more rigorous selection criterion was adopted, where if the quality is less than 6, it would be considered a simple and/or cheap wine, and if it is a value greater than or equal to 6, it would be considered a more select wine, that is, more expensive, allowing the system user (in this case the owner of the wine production) to drink attitudes regarding the quality of the crop that was produced, being able to sell at higher or lower prices.

## Database Normalization
The normalization of the two databases (white and red wine) was done as follows:
Initially, it was found that there was no standardization of the separation of decimal places, that is, for the same row or column, values ​​with "," and "." were used, for this, all values ​​were standardized with comma, according to the standard used in Excel in Portuguese.
After that, the maximum number of decimal places was standardized to a maximum of two values, as in some cases it was possible to observe more than 10 decimal places.

After completing the formatting part of the fields present in the databases, an analysis was performed to discover values ​​that were outside the standard found for that attribute, that is, if for the chlorides attribute the mean found is 5.8 and has a maximum variation of ± 3, and a value much below or above this maximum variation was found, the entire line that belongs to this attribute would be removed, that is, that wine sample would be removed from the base because it contains values ​​that are too out of the standard and could impair AI learning .
Then, descriptive statistics were performed using the data analysis tool, Microsoft Excel, to display the statistical analysis of the data provided for each of the attributes. When performing this task, two values ​​were considered, the minimum and the interval between the maximum and the minimum value, so the formula was applied: (value - minimum value)/range, where value refers to the values ​​of each attribute .
