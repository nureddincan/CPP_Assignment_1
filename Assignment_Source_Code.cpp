/****************************************************************************
**							 SAKARYA ÜNÝVERSÝTESÝ
**				   BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**					    BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**					      PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**	
**				    	ÖDEV NUMARASI     : 1
**				    	ÖÐRENCÝ ADI       : Nureddin Can ERDEÐER
**                      ÖÐRENCÝ NUMARASI  : B231210041
**                      DERS GRUBU        : C 
****************************************************************************/

#include <iostream>
#include <cstdlib> // To use the rand() and srand() functions
#include <ctime> // To use the time() function
#include <string> // To use string data type
#include <iomanip> // To use fixed and setprecision
#include <cfloat> // To use the FLT_MAX INT_MAX 

using namespace std;

// Create a product structure data type that includes members such as name, stock quantity, buying price, sales price, VAT rate, etc. 
struct product {
    string nameOfProduct;
    int stockCount;
    float buyingPrice;
    float salePrice;
    int rateOfVat;
};
    
// Here we create a structure data type that contains the monthly money. Students were told that the monthly expenses are fixed.
struct expenses {
    float rent;
    float staffSalaries;
    float electric;
    float water;
    float otherExpenses;
};
		
expenses monthlyExpenses = { 30.5F, 15.5F, 25.3F, 10.09F, 5.0F };
		
// Total monthly expense
float totalMonthlyExpenses = monthlyExpenses.rent + monthlyExpenses.staffSalaries + monthlyExpenses.electric + monthlyExpenses.water + monthlyExpenses.otherExpenses;

int main() {
    srand(time(0)); // To generate random numbers

	/* Let's assume that the products sold by the company are given in the string firmaurun="mouse,20,51.00,20,microphone, 
	   89.50,mobile phone,66.40,desktop computer,45.09,laptop,96.50,…" */
	string companyProducts = 
        "Mouse,20,51.00,20,"
        "Microphone,20,89.50,20,"
        "Mobile Phone,20,66.40,20,"
        "Desktop Computer,20,45.09,20,"
        "Laptop,20,96.50,20,"
        "Keyboard,20,44.50,20,"
        "Smartwatch,20,35.60,20,"
        "Headphone,20,30.60,20,"
        "Television,20,70.80,20,"
        "Tablet,20,40.40,20,"
        "Game Console,20,35.80,20,"
        "Drone,20,24.90,20,"
        "Printer,20,53.00,20,"
        "Mousepad,20,10.50,20,"
        "Webcam,20,14.50,20,"
        "Vacuum Cleaner,20,14.30,20,"
        "Monitor,20,35.00,20,"
        "Speaker,20,25.50,20,"
        "Dishwasher,20,65.30,20,"
        "Washing Machine,20,76.50,20,";
    
    // Array to hold products
    product products[20];
    
	// The process of transferring product information to the array by processing the companyProducts string
    size_t start = 0, end;
    int productIndex = 0;

	// This loop breaks apart the comma-separated product information and transfers it to the products array.	
    while ( (end = companyProducts.find(',', start)) != -1 && productIndex < 20) {
        products[productIndex].nameOfProduct = companyProducts.substr(start, end - start); // Product name
        start = end + 1;

        end = companyProducts.find(',', start);
        products[productIndex].stockCount = stoi(companyProducts.substr(start, end - start)); // Stock quantity
        start = end + 1;

        end = companyProducts.find(',', start);
        products[productIndex].buyingPrice = stof(companyProducts.substr(start, end - start)); // Buying price
        start = end + 1;

        end = companyProducts.find(',', start);
        products[productIndex].rateOfVat = stoi(companyProducts.substr(start, end - start)); // VAT rate
        start = end + 1;

        // Initially the sales price is set to 0, it will be calculated later
        products[productIndex].salePrice = 0.0F;
        productIndex++;
    }

    // Let the selling price be determined randomly as the buying price of the product + (minimum 30% - maximum 50% of the buying price).
    for (int i = 0; i < 20; ++i) {
        float randomSaleRate = 30 + (rand() % 21);
        float priceWithoutVat = products[i].buyingPrice + (products[i].buyingPrice * randomSaleRate / 100.0F); // Price without vat
        products[i].salePrice = priceWithoutVat * (1 + products[i].rateOfVat / 100.0F); // Price with vat
    }
	
	// To show the 2 digits after the point
	cout << fixed << setprecision(2);

    /* Buying price: The user must give the buying price increase once a month, 
	   once every two months, once every three months, or once every four months. The increase rate must also be given */
    int frequency;
    float increaseRate;
    do {
    	cout << "Please enter the frequency of price increases (1: monthly, 2: every 2 months, 3: every 3 months, 4: every 4 months): ";
    	cin >> frequency;
    	if(frequency < 1 || frequency > 4) {
    		cout << "Invalid frequency! Please enter a value between 1 and 4." << endl;
		}
	} while (frequency < 1 || frequency > 4);
    
    do {
    	cout << "Please enter the rate of price increase (e.g., 5 for 5%): ";
    	cin >> increaseRate;
    	if(increaseRate <= 0 ) {
    		cout << "Invalid rate! Increase rate must be positive!" <<  endl;
		}
	} while (increaseRate <= 0);

    // Variables for monthly statistics
    float yearlyProfit = 0.0F;
    int yearlySales[20] = {0}; // Total annual sales of each product
    float yearlyProfitByProduct[20] = {0.0F}; // Total annual profit of each product
	
	string months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

	// This loop performs monthly profit-loss analysis by calculating product sales and stock status every 12 months.
    for (int month = 1; month <= 12; month++) {
		
    	// Prints months on the screen in order
        cout << "\n--- " << months[month-1] << " ---" << endl;
        
        float monthlyProfit = 0.0F;
        int mostSoldIndex = 0, leastSoldIndex = 0;
        
        // FLT_MAX and INT_MAX are used to determine the starting values ??of the algorithms.
        // In this way, the algorithm is updated whenever any actual value is better than the initial values.
        float maxProfit = 0.0F, minProfit = FLT_MAX;
        int maxSoldAmount = 0, minSoldAmount = INT_MAX;

        for (int i = 0; i < 20; ++i) {
            // Each product is randomly selected and sold on a monthly basis, with a minimum of 60% and a maximum of 80% of the stock.
            float randomRate = 60 + (rand() % 21);
            int soldAmount = products[i].stockCount * (randomRate / 100.0F);
            yearlySales[i] += soldAmount;

            // Profit and cost
            float income = soldAmount * products[i].salePrice; // Income
            float cost = soldAmount * products[i].buyingPrice; // Cost
            float turnover = income - cost; // Turnover
            float profit = turnover - turnover * 16.67 / 100; // We added 20% VAT, we subtract it again. We wrote 16.67% because 20% of 100 is 120, 16.67% of 120 is 20.

            yearlyProfitByProduct[i] += profit;
            monthlyProfit = monthlyProfit + profit - totalMonthlyExpenses;

            // Stock is being updated
            products[i].stockCount -= soldAmount;

            // Stock quantity calculation; 2 * remaining stock + randomly determined as min 70% - max 100% of the sold quantity.
            products[i].stockCount = (2 * products[i].stockCount) + (soldAmount * (70 + (rand() % 31)) / 100.0F);

            // Increase the buying price
            if (month % frequency == 0) {
                products[i].buyingPrice += products[i].buyingPrice * (increaseRate / 100.0F);
            }

            // Let the selling price be determined randomly as the buying price of the product + (minimum 30% - maximum 50% of the buying price).
            float randomSaleRate = 30 + (rand() % 21);
            float newPriceWithoutVat = products[i].buyingPrice + (products[i].buyingPrice * randomSaleRate / 100.0F); // Price without vat
            products[i].salePrice = newPriceWithoutVat * (1 + products[i].rateOfVat / 100.0F); // Price with vat

            // Statistics are being updated
            if (soldAmount > maxSoldAmount) {
                maxSoldAmount = soldAmount;
                mostSoldIndex = i;
            }
            if (soldAmount < minSoldAmount) {
                minSoldAmount = soldAmount;
                leastSoldIndex = i;
            }
            if (profit > maxProfit) {
                maxProfit = profit;
            }
            if (profit < minProfit) {
                minProfit = profit;
            }   
        }
        
        yearlyProfit += monthlyProfit;

        // Monthly report
        cout << "Monthly Profit: " << monthlyProfit << " USD" << endl;
        cout << "Most Sold Product: " << products[mostSoldIndex].nameOfProduct
             << " (" << maxSoldAmount << " units)" << endl;
        cout << "Least Sold Product: " << products[leastSoldIndex].nameOfProduct
             << " (" << minSoldAmount << " units)" << endl;
        cout << "Highest Profit Product: " << products[mostSoldIndex].nameOfProduct
             << " (" << maxProfit << " USD)" << endl;
        cout << "Lowest Profit Product: " << products[leastSoldIndex].nameOfProduct
             << " (" << minProfit << " USD)" << endl;
             
        // Create a string for your company for each subsequent month. The "Name" will remain the same while creating this string.
		string updatedFirmaUrun = "Product Name  | Stock Count | Buying Price | VAT Rate\n";
		updatedFirmaUrun += "----------------------------------------------------------\n";

		for (int i = 0; i < 20; ++i) {
    		updatedFirmaUrun += products[i].nameOfProduct + " | " +
                to_string(products[i].stockCount) + " | " +
                to_string(products[i].buyingPrice) + " | " +
                to_string(products[i].rateOfVat) + "\n";
		}
    }

	// In this section, the best and least selling products and the products that bring the highest and lowest profits are determined based on annual sales and profit data.
	int maxSales = yearlySales[0], mostSoldYearlyIndex = 0;
	int minSales = yearlySales[0], leastSoldYearlyIndex = 0;
	int maxProfit = yearlyProfitByProduct[0], maxProfitIndex = 0;
	int minProfit = yearlyProfitByProduct[0], minProfitIndex = 0;

	for (int i = 1; i < 20; i++) {
    	// Identifies the best and least selling products
    	if (yearlySales[i] > maxSales) {
     	   	maxSales = yearlySales[i];
     		mostSoldYearlyIndex = i;
   		}
   		if (yearlySales[i] < minSales) {
        	minSales = yearlySales[i];
        	leastSoldYearlyIndex = i;
    	}
    	// Identifies the highest and lowest profit-generating products
    	if (yearlyProfitByProduct[i] > maxProfit) {
        	maxProfit = yearlyProfitByProduct[i];
        	maxProfitIndex = i;
    	}
    	if (yearlyProfitByProduct[i] < minProfit) {
        	minProfit = yearlyProfitByProduct[i];
        	minProfitIndex = i;
    	}
	}
	
	cout << "\n--- Year-End Summary ---" << endl;
    cout << "Total Yearly Profit: " << yearlyProfit << " USD" << endl;
    cout << "Most Sold Product of the Year: " << products[mostSoldYearlyIndex].nameOfProduct << " (" << yearlySales[mostSoldYearlyIndex] << " units)" << endl;
    cout << "Least Sold Product of the Year: " << products[leastSoldYearlyIndex].nameOfProduct << " (" << yearlySales[leastSoldYearlyIndex] << " units)" << endl;
    cout << "Highest Yearly Profit Product: " << products[maxProfitIndex].nameOfProduct << " (" << maxProfit << " USD)" << endl;
	cout << "Lowest Yearly Profit Product: " << products[minProfitIndex].nameOfProduct << " (" << minProfit << " USD)" << endl;

	return 0;
}
