#ifndef LCNC_LC_CRT_LOCALE_H
#define LCNC_LC_CRT_LOCALE_H

// Locale categories for setlocale
#define LC_ALL      0   // Set or query all categories
#define LC_COLLATE  1   // String collation category
#define LC_CTYPE    2   // Character classification and conversion category
#define LC_MONETARY 3   // Monetary formatting category
#define LC_NUMERIC  4   // Numeric formatting category
#define LC_TIME     5   // Date and time formatting category

// NULL pointer constant
#define NULL ((void *)0)


// TODO: Decide whether or not this is meant to be in locale.c or locale.h
typedef struct {
    const char *locale_name;            // Name of the locale (e.g., "en_US.UTF-8")

    // Text Sorting and Collation
    const char *collation_rules;        // Rules for string collation and sorting

    // Numeric and Monetary Formatting
    const char *numeric_format;         // Numeric formatting rules
    const char *monetary_format;        // Monetary formatting rules

    // Date and Time Formatting
    const char *date_format;            // Date formatting rules
    const char *time_format;            // Time formatting rules

    // Measurement Units
    const char *measurement_units;      // Measurement units and conversion factors

    // Character Classification and Case Conversion
    const char *char_classification;    // Character classification rules
    const char *case_conversion;        // Case conversion rules

    // Text Boundary Analysis
    const char *text_boundary_rules;    // Text boundary analysis rules

    // Calendar Systems and Local Holidays
    const char *calendar_system;        // Calendar system rules
    const char *local_holidays;         // Local holidays and observances

    // Language-Specific Rules
    const char *language_rules;         // Language-specific grammar and syntax rules

    // Cultural Preferences and Norms
    const char *cultural_preferences;   // Cultural preferences and norms

    // Geographical and Regional Information
    const char *geographical_info;      // Geographical and regional information

    // Custom Extensions or Additional Data
    const char *custom_extensions;      // Custom extensions or additional data specific to the locale

    // Reserved for future extensions or additional members
    // Add more members as needed for specific locale data
} locale_t;


// Locale function prototypes
char *setlocale(int category, const char *locale);
locale_t duplocale(locale_t base);
void freelocale(locale_t locobj);
locale_t newlocale(int category_mask, const char *locale, locale_t base);
locale_t uselocale(locale_t locobj);

#endif // LOCALE_H
