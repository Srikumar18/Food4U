# 🍕 Food Delivery Management System in C

This project is a **simple food delivery application** implemented in **C**. It enables users to order food by selecting items or choosing a restaurant. Users can specify dietary preferences, customize their cart, and enjoy various discounts. The system also allows users to rate and review food, restaurants, and delivery partners.

---

## 📚 **Features**
- **Menu Display:** View available food items along with prices and dietary details.
- **Order Placement:** Place and customize orders by food or restaurant.
- **Cart Customization:** Add, modify, and delete items from the cart.
- **Order History:** View past orders and purchase details.
- **Recommendation System:** Suggests items based on user preferences using the Apriori algorithm.
- **Bill Generation:** Applies discounts, coupons, and taxes while generating bills.
- **Shortest Path Calculation:** Uses Dijkstra’s algorithm to calculate distance between the user, restaurant, and driver.
- **Driver Assignment:** Selects the best driver based on distance and ratings.
- **Review and Rating:** Users can review food, restaurants, and drivers.
- **User Queries:** Allows users to submit queries, which can be addressed by the admin.

---

## 🚀 **How to Run the Project**

### 1️⃣ **Open Replit**
- Go to [Replit](https://replit.com/) and create a new C project.

### 2️⃣ **Upload Files**
- Upload all the project files to your Replit workspace.
- Ensure the following files are included:

## 📂 **Project Structure**
/Food_delivery_management
- main.c               # Main driver program
- menu.h               # Function definitions and structure declarations
- menu.c               # Generates menu based on user preferences
- Bill_generation.c    # Generates bill, applies discounts and taxes
- choiceselection.c    # Allows selection by food or restaurant
- dijkstras.c          # Computes shortest path using Dijkstra's algorithm
- edit.c               # Handles cart editing and customization
- Login.c              # Manages user login and query handling
- registration.c       # Handles user registration
- review.c             # Collects and stores reviews for food, drivers, and restaurants
- Userdet.csv          # Stores registered user details
- Coupons.txt          # Contains number of coupons for each user
- Custchurn.txt        # Stores the month of last purchase for each user
- Driverdetails.txt    # Stores driver details and locations
- Food.csv             # Logs all purchases for recommendation purposes
- Queries.txt          # Stores user queries for admin review
- Review_driver.txt    # Stores driver ratings and review counts
- Review_rest.txt      # Stores restaurant ratings and review counts
- Review_food.txt      # Stores food item ratings and review counts
