# Problem 059 - OJ 的继承与派生 - Solution Summary

## Problem Overview
Implement a class hierarchy for an Online Judge system with inheritance:
- `BaseJudger`: Base class with virtual methods
- `ICPCJudger`: ICPC-style judging (multiple submissions, highest score)
- `OIJudger`: OI-style judging (single submission, trailing space handling)
- `SpacialJudger`: Special scoring with linear time/memory penalties

## Solution Approach

### BaseJudger Implementation
- Constructor allocates memory for answer string using `new char[]`
- Destructor frees memory using `delete[]`
- Virtual `Submit()` method for derived classes to override
- Protected `CheckAnswer()` method for exact string comparison

### ICPCJudger Implementation
- Inherits from BaseJudger
- Multiple submissions allowed
- Scoring: 100 if time/memory within limits and answer correct, 0 otherwise
- Keeps highest score across all submissions

### OIJudger Implementation
- Inherits from BaseJudger
- Single submission only - second submission results in score of 0
- Overrides `CheckAnswer()` to handle trailing spaces
- Implements trimTrailingSpaces() helper function
- Processes both answer and output line by line, removing trailing spaces

### SpacialJudger Implementation
- Inherits from BaseJudger
- Complex scoring based on time and memory usage
- Time score: 100 if ≤ full_score_time, 0 if ≥ time_limit, linear between
- Memory score: Similar linear interpolation
- Final score: floor(time_score × memory_score / 100)
- Keeps highest score across multiple submissions

## Test Results

### Local Testing
- Tested ICPCJudger with multiple submissions ✓
- Tested OIJudger with trailing spaces ✓
- Tested OIJudger with multiple submissions (returns 0) ✓
- Tested SpacialJudger with linear scoring ✓

### Online Judge Submission
**Submission ID**: 766493
**Status**: Accepted
**Score**: 100/100
**Test Points**: 10/10 passed

All test groups passed:
- Groups 1-4: ICPCJudger tests
- Groups 5-7: SpacialJudger tests
- Groups 8-10: OIJudger tests

## Key Implementation Details

1. **Memory Management**: Proper use of `new`/`delete` for dynamic memory
2. **Virtual Functions**: Correct use of `override` keyword
3. **String Handling**: Careful processing of trailing spaces for OIJudger
4. **Integer Arithmetic**: Proper floor division for SpacialJudger scoring
5. **State Management**: Tracking submission count for OIJudger

## Complexity Analysis
- Time Complexity: O(n) for string comparison where n is answer length
- Space Complexity: O(n) for storing answer string
- All operations are efficient and within time/memory limits

## Submission Count
- **Total Submissions**: 1/5
- **Successful**: 1
- **Remaining Attempts**: 4

## Conclusion
The implementation successfully passes all test cases on the first submission, demonstrating correct understanding of:
- C++ inheritance and polymorphism
- Virtual functions and method overriding
- Dynamic memory management
- String processing and comparison
- Linear interpolation for scoring
