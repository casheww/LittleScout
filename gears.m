seconds_per_sidereal_day = (23*60*60) + (56*60) + 4
ra_rev_per_minute = 1 / (seconds_per_sidereal_day/60)
ra_rev_per_day = ra_rev_per_minute*60*24

ra_ratio = 1800;
ra_drive_rev_per_minute = ra_rev_per_minute * ra_ratio
ra_drive_rev_per_second = ra_drive_rev_per_minute / 60

ra_steps_per_rev = 200;
ra_microstep = 16
ra_drive_steps_per_second = ra_drive_rev_per_second * ra_steps_per_rev * ra_microstep    % 66.8493
sidereal_step_period_us = 1/ra_drive_steps_per_second * 1e6

target_ra_goto_rev_per_minute = 0.5;
ra_microstep = 1
ra_drive_goto_rev_per_minute = target_ra_goto_rev_per_minute * ra_ratio
ra_drive_goto_steps_per_second = ra_drive_goto_rev_per_minute/60 * ra_steps_per_rev * ra_microstep
goto_step_period_us = 1/ra_drive_goto_steps_per_second * 1e6
