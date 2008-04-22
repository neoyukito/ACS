package alma.acs.eventbrowser.views;

import org.eclipse.jface.viewers.ColumnLabelProvider;

public class EventTypeLabelProvider extends ColumnLabelProvider {
	@Override
	public String getText(Object element) {
		if (element instanceof EventData)
			return ((EventData) element).getEventTypeName();
		return super.getText(element);
	}
}
