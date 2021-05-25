#include <executor/grep_structure.h>

bool regex_filter::matches(QString text, line_number_t) {
    initialize_regex();

    return regex->match(text).hasMatch() ^ is_inverted;
}

void regex_filter::initialize_regex() {
    if(regex != nullptr)
        return;

    regex = std::make_unique<QRegularExpression>(search_query, (is_case_sensitive) ? QRegularExpression::NoPatternOption : QRegularExpression::CaseInsensitiveOption);
    regex->optimize();
}

bool regex_filter::same_as(filter& b) {
    auto f = dynamic_cast<regex_filter*>(&b);
    if(f == nullptr) {
        return false;
    }

    return f->search_query == search_query &&
            f->is_case_sensitive == is_case_sensitive &&
            f->is_regex == is_regex &&
            f->is_inverted == is_inverted;
}

QString regex_filter::name() const {
    QString cs = is_case_sensitive ? "C" : "";
    QString rx = is_regex ? "R" : "";
    QString inv = is_inverted ? "I" : "";
    QString prefix = "{" + cs + rx + inv + "} ";


    return prefix + search_query;
}

bool filter_above::matches(QString, line_number_t line_num) {
    return first_line <= line_num;
}

bool filter_above::same_as(filter& b) {
    auto f = dynamic_cast<filter_above*>(&b);
    if(f == nullptr) {
        return false;
    }

    return f->first_line == first_line;
}

QString filter_above::name() const {
    return QString("Below ").append(QString::number(first_line));
}

bool filter_below::matches(QString, line_number_t line_num) {
    return last_line >= line_num;
}

bool filter_below::same_as(filter& b) {
    auto f = dynamic_cast<filter_below*>(&b);
    if(f == nullptr) {
        return false;
    }

    return f->last_line == last_line;
}

QString filter_below::name() const {
    return QString("Above ").append(QString::number(last_line));
}
