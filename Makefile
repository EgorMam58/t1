.PHONY: clean All

All:
	@echo "----------Building project:[ l1 - Debug ]----------"
	@cd "l1" && "$(MAKE)" -f  "l1.mk"
clean:
	@echo "----------Cleaning project:[ l1 - Debug ]----------"
	@cd "l1" && "$(MAKE)" -f  "l1.mk" clean
