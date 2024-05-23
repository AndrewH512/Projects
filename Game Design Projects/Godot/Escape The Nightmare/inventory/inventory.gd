class_name Inv
extends Resource

signal update

@export var slots: Array[InvSlot]

# Inserting into the Inv
func insert(item:InvItem):
	var itemslots = slots.filter(func(slot):return slot.item == item)
	if !itemslots.is_empty():
		itemslots[0].amount += 1
	else:
		# Already existing
		var emptyslots = slots.filter(func(slot):return slot.item == null)
		if !emptyslots.is_empty():
			emptyslots[0].item = item
			itemslots[0].amount - 1
	update.emit()
