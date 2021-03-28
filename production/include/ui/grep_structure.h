#ifndef GREP_STRUCTURE_H
#define GREP_STRUCTURE_H

#include <QString>
#include <QRegularExpression>

#include "line_descriptor.h"

class filter {
public:
    virtual bool matches(QString, line_number_t) = 0;
    virtual bool same_as(filter&) = 0;
    virtual QString name() const = 0;


    virtual ~filter() {};
};

class regex_filter : public filter {
public:
    QString search_query;
    bool is_regex;
    bool is_case_sensitive;
    bool is_inverted;

    virtual bool matches(QString text, line_number_t) override;
    virtual bool same_as(filter&) override;
    virtual QString name() const override;
private:
    void initialize_regex();

    std::unique_ptr<QRegularExpression> regex;
};

class filter_above : public filter {
public:
    line_number_t first_line;
    virtual bool matches(QString, line_number_t) override;
    virtual bool same_as(filter&) override;
    virtual QString name() const override;
};

class filter_below : public filter {
public:
    line_number_t last_line;
    virtual bool matches(QString, line_number_t) override;
    virtual bool same_as(filter&) override;
    virtual QString name() const override;
};

#endif // GREP_STRUCTURE_H
