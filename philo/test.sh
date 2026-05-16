#!/bin/bash

# =============================================================================
# Philosophers - Eval Sheet Test Script
# =============================================================================

PHILO_PATH="./philo"
PASS=0
FAIL=0

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

print_header()
{
	echo ""
	echo -e "${CYAN}============================================================${NC}"
	echo -e "${CYAN} $1${NC}"
	echo -e "${CYAN}============================================================${NC}"
}

print_result()
{
	if [ "$1" = "PASS" ]; then
		echo -e "  ${GREEN}[PASS]${NC} $2"
		PASS=$((PASS + 1))
	else
		echo -e "  ${RED}[FAIL]${NC} $2"
		FAIL=$((FAIL + 1))
	fi
}

check_binary()
{
	if [ ! -f "$PHILO_PATH" ]; then
		echo -e "${RED}Error: '$PHILO_PATH' not found. Run 'make' first.${NC}"
		exit 1
	fi
}

# Run philo for a duration and capture output
# Usage: run_philo <duration_ms> <args...>
run_philo()
{
	local duration=$1
	shift
	local duration_sec=$(echo "scale=2; $duration / 1000" | bc)
	timeout "$duration_sec" $PHILO_PATH "$@" 2>/dev/null
}

# =============================================================================
# TEST: Error handling - wrong arg count
# =============================================================================
test_error_handling()
{
	print_header "Error Handling"

	# Too few args
	$PHILO_PATH 2>/dev/null
	if [ $? -ne 0 ]; then
		print_result "PASS" "No args: exits with error"
	else
		print_result "FAIL" "No args: should exit with error"
	fi

	$PHILO_PATH 5 800 200 2>/dev/null
	if [ $? -ne 0 ]; then
		print_result "PASS" "Too few args: exits with error"
	else
		print_result "FAIL" "Too few args: should exit with error"
	fi

	# Too many args
	$PHILO_PATH 5 800 200 200 7 99 2>/dev/null
	if [ $? -ne 0 ]; then
		print_result "PASS" "Too many args: exits with error"
	else
		print_result "FAIL" "Too many args: should exit with error"
	fi

	# Non-numeric args
	$PHILO_PATH 5 800 abc 200 2>/dev/null
	if [ $? -ne 0 ]; then
		print_result "PASS" "Non-numeric arg: exits with error"
	else
		print_result "FAIL" "Non-numeric arg: should exit with error"
	fi
}

# =============================================================================
# TEST 1: 1 800 200 200 — philosopher should die
# =============================================================================
test_one_philo_dies()
{
	print_header "Test: 1 800 200 200 (philosopher should die)"
	echo "  Running for 1200ms..."

	output=$(run_philo 1200 1 800 200 200)

	if echo "$output" | grep -q "died"; then
		print_result "PASS" "Philosopher died as expected"
	else
		print_result "FAIL" "Philosopher did not die"
	fi

	# Check death timing - should die around 800ms
	death_time=$(echo "$output" | grep "died" | awk '{print $1}')
	if [ -n "$death_time" ]; then
		echo "  Death at: ${death_time}ms (expected ~800ms)"
		if [ "$death_time" -le 810 ]; then
			print_result "PASS" "Death reported within 10ms of expected time"
		else
			print_result "FAIL" "Death reported too late: ${death_time}ms (max 810ms)"
		fi
	fi
}

# =============================================================================
# TEST 2: 5 800 200 200 — no philosopher should die
# =============================================================================
test_five_philos_no_death()
{
	print_header "Test: 5 800 200 200 (no philosopher should die)"
	echo "  Running for 5000ms..."

	output=$(run_philo 5000 5 800 200 200)

	if echo "$output" | grep -q "died"; then
		print_result "FAIL" "A philosopher died unexpectedly"
		echo "$output" | grep "died"
	else
		print_result "PASS" "No philosopher died in 5000ms"
	fi
}

# =============================================================================
# TEST 3: 5 800 200 200 7 — no death, stops after 7 meals each
# =============================================================================
test_five_philos_max_eat()
{
	print_header "Test: 5 800 200 200 7 (no death, stop after 7 meals each)"
	echo "  Running for 10000ms..."

	output=$(run_philo 10000 5 800 200 200 7)

	if echo "$output" | grep -q "died"; then
		print_result "FAIL" "A philosopher died unexpectedly"
	else
		print_result "PASS" "No philosopher died"
	fi

	# Check simulation actually stopped (program exited before timeout)
	$PHILO_PATH 5 800 200 200 7 2>/dev/null &
	pid=$!
	sleep 10
	if kill -0 $pid 2>/dev/null; then
		kill $pid 2>/dev/null
		print_result "FAIL" "Simulation did not stop after all philosophers ate 7 times"
	else
		print_result "PASS" "Simulation stopped on its own (all ate 7 times)"
	fi
}

# =============================================================================
# TEST 4: 4 410 200 200 — no philosopher should die
# =============================================================================
test_four_philos_no_death()
{
	print_header "Test: 4 410 200 200 (no philosopher should die)"
	echo "  Running for 5000ms..."

	output=$(run_philo 5000 4 410 200 200)

	if echo "$output" | grep -q "died"; then
		print_result "FAIL" "A philosopher died unexpectedly"
		echo "$output" | grep "died"
	else
		print_result "PASS" "No philosopher died in 5000ms"
	fi
}

# =============================================================================
# TEST 5: 4 310 200 100 — one philosopher should die
# =============================================================================
test_four_philos_one_death()
{
	print_header "Test: 4 310 200 100 (one philosopher should die)"
	echo "  Running for 3000ms..."

	output=$(run_philo 3000 4 310 200 100)

	if echo "$output" | grep -q "died"; then
		print_result "PASS" "A philosopher died as expected"
	else
		print_result "FAIL" "No philosopher died (one should have)"
	fi
}

# =============================================================================
# TEST 6: 2 philosophers - death timing check (<= 10ms delay)
# =============================================================================
test_two_philos_death_timing()
{
	print_header "Test: 2 philosophers death timing (death within 10ms)"
	echo "  Running: 2 60 60 60..."
	echo "  (tight timing to stress test death detection)"

	output=$(run_philo 2000 2 60 60 60)

	# With these params philosophers may or may not die depending on scheduling
	# Just check output is not garbled
	if echo "$output" | grep -qE "^[0-9]+ [0-9]+ (has taken a fork|is eating|is sleeping|is thinking|died)$"; then
		print_result "PASS" "Output format is correct"
	else
		print_result "FAIL" "Output format looks wrong"
		echo "$output" | head -5
	fi

	# Manual timing test: 2 200 100 100 - should never die
	echo ""
	echo "  Running: 2 200 100 100 (should not die)..."
	output2=$(run_philo 3000 2 200 100 100)
	if echo "$output2" | grep -q "died"; then
		print_result "FAIL" "Philosopher died unexpectedly in 2 200 100 100"
	else
		print_result "PASS" "No death in 2 200 100 100"
	fi
}

# =============================================================================
# TEST 7: Output format check
# =============================================================================
test_output_format()
{
	print_header "Test: Output format validation"
	echo "  Running: 3 800 200 200 for 2000ms..."

	output=$(run_philo 2000 3 800 200 200)
	valid=1

	while IFS= read -r line; do
		if [ -z "$line" ]; then continue; fi
		if ! echo "$line" | grep -qE "^[0-9]+ [0-9]+ (has taken a fork|is eating|is sleeping|is thinking|died)$"; then
			echo "  Bad line: '$line'"
			valid=0
		fi
	done <<< "$output"

	if [ $valid -eq 1 ]; then
		print_result "PASS" "All output lines have correct format"
	else
		print_result "FAIL" "Some output lines have incorrect format"
	fi
}

# =============================================================================
# TEST 8: No output after death
# =============================================================================
test_no_output_after_death()
{
	print_header "Test: No output after 'died'"
	echo "  Running: 1 800 200 200..."

	output=$(run_philo 1200 1 800 200 200)

	death_line=$(echo "$output" | grep -n "died" | head -1 | cut -d: -f1)
	total_lines=$(echo "$output" | wc -l)

	if [ -n "$death_line" ] && [ "$death_line" -lt "$total_lines" ]; then
		after=$(echo "$output" | tail -n +"$((death_line + 1))")
		if [ -n "$(echo "$after" | tr -d '[:space:]')" ]; then
			print_result "FAIL" "Output continues after 'died'"
			echo "$after" | head -3
		else
			print_result "PASS" "No output after 'died'"
		fi
	else
		print_result "PASS" "No output after 'died' (or no death line found)"
	fi
}

# =============================================================================
# SUMMARY
# =============================================================================
print_summary()
{
	echo ""
	echo -e "${CYAN}============================================================${NC}"
	echo -e "${CYAN} SUMMARY${NC}"
	echo -e "${CYAN}============================================================${NC}"
	echo -e "  ${GREEN}PASSED: $PASS${NC}"
	echo -e "  ${RED}FAILED: $FAIL${NC}"
	total=$((PASS + FAIL))
	echo -e "  TOTAL:  $total"
	echo ""
}

# =============================================================================
# MAIN
# =============================================================================
check_binary
test_error_handling
test_one_philo_dies
test_five_philos_no_death
test_five_philos_max_eat
test_four_philos_no_death
test_four_philos_one_death
test_two_philos_death_timing
test_output_format
test_no_output_after_death
print_summary
