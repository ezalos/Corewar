.name "LEODESTRUCTOR"
.comment "I DONT NEED COMMENT"

lives:
	live %1
aff r10
aff r19
ld %48, r3
aff r3
ld %49, r3
aff r3
aff r1
fork %:lives
