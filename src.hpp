#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>

class BaseJudger {
public:
    BaseJudger(size_t time_limit, size_t memory_limit, const char *answer)
        : time_limit_(time_limit), memory_limit_(memory_limit), score_(0) {
        // Allocate memory for answer and copy it
        answer_ = new char[strlen(answer) + 1];
        strcpy(answer_, answer);
    }

    virtual void Submit(size_t time, size_t memory, const char *output) = 0;

    size_t GetScore() const { return score_; }

    virtual ~BaseJudger() {
        // Free allocated memory
        delete[] answer_;
    }

protected:
    char *answer_;
    const size_t time_limit_;
    const size_t memory_limit_;
    size_t score_;

    virtual bool CheckAnswer(const char *output) const {
        // the output must equal to the answer
        return strcmp(answer_, output) == 0;
    }
};


class ICPCJudger : public BaseJudger {
public:
    ICPCJudger(size_t time_limit, size_t memory_limit, const char *answer)
        : BaseJudger(time_limit, memory_limit, answer) {}

    void Submit(size_t time, size_t memory, const char *output) override {
        // Check if within limits and answer is correct
        if (time <= time_limit_ && memory <= memory_limit_ && CheckAnswer(output)) {
            score_ = 100;
        }
        // Keep highest score (if already 100, stays 100)
    }
};


class OIJudger : public BaseJudger {
private:
    bool has_submitted_;

    // Helper function to remove trailing spaces from a string
    std::string trimTrailingSpaces(const std::string& str) const {
        size_t end = str.find_last_not_of(" \t");
        return (end == std::string::npos) ? "" : str.substr(0, end + 1);
    }

    // Override CheckAnswer to ignore trailing spaces
    bool CheckAnswer(const char *output) const override {
        std::string ans(answer_);
        std::string out(output);

        // Split by newlines and compare line by line
        std::string ans_processed = "";
        std::string out_processed = "";

        // Process answer
        size_t start = 0, end = 0;
        while ((end = ans.find('\n', start)) != std::string::npos) {
            std::string line = ans.substr(start, end - start);
            ans_processed += trimTrailingSpaces(line) + "\n";
            start = end + 1;
        }
        if (start < ans.length()) {
            ans_processed += trimTrailingSpaces(ans.substr(start));
        }

        // Process output
        start = 0;
        while ((end = out.find('\n', start)) != std::string::npos) {
            std::string line = out.substr(start, end - start);
            out_processed += trimTrailingSpaces(line) + "\n";
            start = end + 1;
        }
        if (start < out.length()) {
            out_processed += trimTrailingSpaces(out.substr(start));
        }

        return ans_processed == out_processed;
    }

public:
    OIJudger(size_t time_limit, size_t memory_limit, const char *answer)
        : BaseJudger(time_limit, memory_limit, answer), has_submitted_(false) {}

    void Submit(size_t time, size_t memory, const char *output) override {
        // If already submitted once, set score to 0
        if (has_submitted_) {
            score_ = 0;
            return;
        }

        has_submitted_ = true;

        // Check if within limits and answer is correct
        if (time <= time_limit_ && memory <= memory_limit_ && CheckAnswer(output)) {
            score_ = 100;
        } else {
            score_ = 0;
        }
    }
};


class SpacialJudger : public BaseJudger {
private:
    const size_t full_score_time_;
    const size_t full_score_memory_;

public:
    SpacialJudger(size_t time_limit, size_t memory_limit,
                  size_t full_score_time, size_t full_score_memory,
                  const char *answer)
        : BaseJudger(time_limit, memory_limit, answer),
          full_score_time_(full_score_time),
          full_score_memory_(full_score_memory) {}

    void Submit(size_t time, size_t memory, const char *output) override {
        // Check if answer is correct
        if (!CheckAnswer(output)) {
            // If answer is wrong, score stays at current value (possibly 0)
            return;
        }

        // Calculate time_score
        size_t time_score;
        if (time <= full_score_time_) {
            time_score = 100;
        } else if (time >= time_limit_) {
            time_score = 0;
        } else {
            // Linear interpolation
            // time_score = 100 - (time - full_score_time_) * 100 / (time_limit_ - full_score_time_)
            time_score = 100 - ((time - full_score_time_) * 100 / (time_limit_ - full_score_time_));
        }

        // Calculate memory_score
        size_t memory_score;
        if (memory <= full_score_memory_) {
            memory_score = 100;
        } else if (memory >= memory_limit_) {
            memory_score = 0;
        } else {
            // Linear interpolation
            memory_score = 100 - ((memory - full_score_memory_) * 100 / (memory_limit_ - full_score_memory_));
        }

        // Calculate final score
        size_t current_score = (time_score * memory_score) / 100;

        // Keep highest score
        if (current_score > score_) {
            score_ = current_score;
        }
    }
};
