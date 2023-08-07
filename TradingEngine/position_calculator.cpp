#include <vector>
#include "../model/stock_price.h"
#include "../model/stock_trade.h"
/**
 * @brief Calculate the profits and losses and update the holdings after executing trades.
 * 
 * This class is responsible for calculating the profits and losses and updating the current holdings
 * after executing trades based on the trading strategy.
 * 
 * @param trades The vector of StockTrade objects representing the trades executed based on the trading strategy.
 * @param holdings The vector of StockPrice objects representing the current holdings of stocks.
 * @param profitsLosses The reference to a double representing the current profits and losses.
 * @param cash The reference to a double representing the current available cash.
 */
void calculatePnL(const std::vector<StockTrade>& trades, std::vector<StockPrice>& holdings, double& profitsLosses, double& cash) {
    for (const StockTrade& trade : trades) {
        auto it = std::find_if(holdings.begin(), holdings.end(), [&trade](const StockPrice& holding) {
            return holding.ticker == trade.ticker;
        });

        if (it != holdings.end()) {
            double currentQuantity = it->price;
            double newQuantity = currentQuantity + trade.qty;
            if (newQuantity <= 0) {
                holdings.erase(it);
            } else {
                it->price = newQuantity;
            }
        } else {
            // Add a new holding for the stock if it doesn't exist in the holdings
            holdings.push_back({ trade.ticker, trade.qty });
        }

        // Update cash and profits & losses based on the trade
        cash -= trade.qty * trade.price;
        profitsLosses += trade.qty * (trade.price - trade.averagePrice);
    }
}